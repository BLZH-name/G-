#pragma once
#include<iostream>
#include<fstream>
#include <bitset>
#include<vector>
#include<string>
#include <unordered_map>
#include<queue>
#include<io.h>
#include<algorithm>
#include<windows.h>  

// 避免byte符号冲突（C++17+Windows.h兼容）
#define NO_RPCNDR_H

// 哈夫曼树节点结构体（全局复用）
struct Node {
    uint8_t data;
    int freq;
    Node* left;
    Node* right;
    Node(uint8_t c, int t) :data(c), freq(t), left(nullptr), right(nullptr) {}
    Node(Node* l, Node* r) :data(0), freq(l->freq + r->freq), left(l), right(r) {}
    ~Node() { delete left; delete right; } // 递归释放内存
};

// 优先队列比较器（最小堆）
struct CompareNode {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

// 工具类：封装通用文件操作（路径判断、目录创建等）
class FileUtils {
public:
    // 判断路径是否存在
    static bool pathExists(const std::string& path) {
        DWORD attr = GetFileAttributesA(path.c_str());
        return attr != INVALID_FILE_ATTRIBUTES;
    }

    // 判断路径是否为目录
    static bool isDirectory(const std::string& path) {
        DWORD attr = GetFileAttributesA(path.c_str());
        if (attr == INVALID_FILE_ATTRIBUTES) return false;
        return (attr & FILE_ATTRIBUTE_DIRECTORY) != 0;
    }

    // 获取文件大小（支持>4GB大文件）
    static uint64_t getFileSize(const std::string& filePath) {
        HANDLE hFile = CreateFileA(filePath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL,
            OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE) {
            std::cerr << "警告：无法打开文件 " << filePath << "（错误码：" << GetLastError() << "）" << std::endl;
            return 0;
        }

        DWORD lowSize = GetFileSize(hFile, NULL);
        DWORD highSize = 0;
        if (lowSize == INVALID_FILE_SIZE && GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
            highSize = GetFileSize(hFile, &lowSize);
        }
        CloseHandle(hFile);
        return (static_cast<uint64_t>(highSize) << 32) | lowSize;
    }

    // 递归创建目录（Windows专用）
    static bool createDirRecursive(const std::string& dirPath) {
        std::string winPath = dirPath;
        std::replace(winPath.begin(), winPath.end(), '/', '\\');

        // 处理根路径
        if (winPath.size() >= 2 && winPath[1] == ':') {
            if (winPath.size() == 2 || (winPath.size() == 3 && winPath[2] == '\\')) {
                return true;
            }
        }

        // 逐段创建目录
        size_t pos = 0;
        while ((pos = winPath.find('\\', pos + 1)) != std::string::npos) {
            std::string subDir = winPath.substr(0, pos);
            if (!pathExists(subDir)) {
                if (!CreateDirectoryA(subDir.c_str(), NULL)) {
                    DWORD err = GetLastError();
                    if (err != ERROR_ALREADY_EXISTS) {
                        std::cerr << "警告：创建目录失败 " << subDir << "（错误码：" << err << "）" << std::endl;
                        return false;
                    }
                }
            }
        }

        // 创建最后一级目录
        if (!pathExists(winPath)) {
            if (!CreateDirectoryA(winPath.c_str(), NULL)) {
                DWORD err = GetLastError();
                if (err != ERROR_ALREADY_EXISTS) {
                    std::cerr << "警告：创建目录失败 " << winPath << "（错误码：" << err << "）" << std::endl;
                    return false;
                }
            }
        }
        return true;
    }
};

// 抽象基类：定义压缩/解压核心接口
class ICompressor {
public:
    virtual ~ICompressor() {} // 虚析构函数，确保派生类正确释放

    // 纯虚接口：压缩（子类必须实现）
    virtual bool compress(const std::string& inputPath, const std::string& outputPath) = 0;

    // 纯虚接口：解压（子类必须实现）
    virtual bool decompress(const std::string& inputPath, const std::string& outputPath) = 0;
};

// 单文件压缩/解压实现类
class SingleFileCompressor : public ICompressor {
private:
    // 统计单个文件的字节频率
    std::unordered_map<uint8_t, int> countFreq(const std::string& filePath) {
        std::unordered_map<uint8_t, int> freq;
        std::ifstream in(filePath, std::ios::binary);
        if (!in) {
            std::cerr << "错误：读取文件失败 " << filePath << std::endl;
            exit(1);
        }

        uint8_t byte;
        while (in.read(reinterpret_cast<char*>(&byte), 1)) {
            freq[byte]++;
        }
        in.close();
        return freq;
    }

    // 构建哈夫曼树
    Node* buildTree(std::unordered_map<uint8_t, int>& freq) {
        std::priority_queue<Node*, std::vector<Node*>, CompareNode> minHeap;
        for (const auto& p : freq) {
            minHeap.push(new Node(p.first, p.second));
        }

        while (minHeap.size() > 1) {
            auto left = minHeap.top(); minHeap.pop();
            auto right = minHeap.top(); minHeap.pop();
            minHeap.push(new Node(left, right));
        }

        return minHeap.empty() ? nullptr : minHeap.top();
    }

    // 生成哈夫曼编码表
    void generateCodes(Node* root, std::string code, std::unordered_map<uint8_t, std::string>& codes) {
        if (!root) return;
        if (!root->left && !root->right) {
            codes[root->data] = code.empty() ? "0" : code;
            return;
        }
        generateCodes(root->left, code + "0", codes);
        generateCodes(root->right, code + "1", codes);
    }

public:
    // 实现抽象接口：单文件压缩
    bool compress(const std::string& inputPath, const std::string& outputPath) override {
        // 验证输入路径
        if (!FileUtils::pathExists(inputPath)) {
            std::cerr << "错误：输入文件不存在 " << inputPath << std::endl;
            return false;
        }
        if (FileUtils::isDirectory(inputPath)) {
            std::cerr << "错误：输入路径是目录，单文件压缩仅支持文件" << std::endl;
            return false;
        }

        // 统计频率→构建树→生成编码
        auto freq = countFreq(inputPath);
        if (freq.empty()) {
            std::cout << "警告：文件 " << inputPath << " 为空" << std::endl;
            return true;
        }

        auto root = buildTree(freq);
        std::unordered_map<uint8_t, std::string> codes;
        generateCodes(root, "", codes);
        delete root;

        // 写入压缩文件
        std::ofstream out(outputPath, std::ios::binary);
        if (!out) {
            std::cerr << "错误：无法创建输出文件 " << outputPath << std::endl;
            return false;
        }

        // 写入编码表大小
        int codeSize = codes.size();
        out.write(reinterpret_cast<char*>(&codeSize), sizeof(codeSize));

        // 写入编码表条目
        for (const auto& p : codes) {
            uint8_t byte = p.first;
            const std::string& code = p.second;
            int len = code.size();

            out.write(reinterpret_cast<char*>(&byte), 1);
            out.write(reinterpret_cast<char*>(&len), sizeof(len));

            // 编码内容位打包
            std::bitset<8> bits;
            for (int i = 0; i < len; ++i) {
                bits[i % 8] = (code[i] == '1');
                if (i % 8 == 7 || i == len - 1) {
                    out.put(static_cast<char>(bits.to_ulong()));
                    bits.reset();
                }
            }
        }

        // 生成编码位流
        std::string bitStream;
        std::ifstream in(inputPath, std::ios::binary);
        uint8_t byte;
        while (in.read(reinterpret_cast<char*>(&byte), 1)) {
            bitStream += codes[byte];
        }
        in.close();

        // 处理填充位
        int pad = 8 - (bitStream.size() % 8);
        if (pad != 8) {
            bitStream += std::string(pad, '0');
        }
        out.write(reinterpret_cast<char*>(&pad), sizeof(pad));

        // 位流转字节写入
        for (size_t i = 0; i < bitStream.size(); i += 8) {
            std::string byteStr = bitStream.substr(i, 8);
            std::bitset<8> bits(byteStr);
            out.put(static_cast<char>(bits.to_ulong()));
        }

        out.close();
        std::cout << "单文件压缩完成：" << outputPath << std::endl;
        return true;
    }

    // 实现抽象接口：单文件解压
    bool decompress(const std::string& inputPath, const std::string& outputPath) override {
        // 验证输入路径
        if (!FileUtils::pathExists(inputPath)) {
            std::cerr << "错误：压缩包不存在 " << inputPath << std::endl;
            return false;
        }

        std::ifstream in(inputPath, std::ios::binary);
        if (!in) {
            std::cerr << "错误：打开压缩包失败 " << inputPath << std::endl;
            return false;
        }

        // 读取编码表大小
        int codeSize;
        if (!in.read(reinterpret_cast<char*>(&codeSize), sizeof(codeSize))) {
            std::cerr << "错误：压缩包损坏，无法读取编码表大小" << std::endl;
            in.close();
            return false;
        }

        // 构建反向编码表
        std::unordered_map<std::string, uint8_t> codeMap;
        for (int i = 0; i < codeSize; ++i) {
            uint8_t byte;
            int len;
            if (!in.read(reinterpret_cast<char*>(&byte), 1) || !in.read(reinterpret_cast<char*>(&len), sizeof(len))) {
                std::cerr << "错误：压缩包损坏，编码表读取失败" << std::endl;
                in.close();
                return false;
            }

            std::string code;
            int bytes = (len + 7) / 8;
            for (int j = 0; j < bytes; ++j) {
                uint8_t b;
                if (!in.read(reinterpret_cast<char*>(&b), 1)) {
                    std::cerr << "错误：压缩包损坏，编码内容读取失败" << std::endl;
                    in.close();
                    return false;
                }
                std::bitset<8> bits(b);
                for (int k = 0; k < 8 && code.size() < len; ++k) {
                    code += bits[k] ? "1" : "0";
                }
            }
            codeMap[code] = byte;
        }

        // 读取填充位
        int pad;
        if (!in.read(reinterpret_cast<char*>(&pad), sizeof(pad))) {
            std::cerr << "错误：压缩包损坏，无法读取填充位" << std::endl;
            in.close();
            return false;
        }

        // 读取压缩数据并转换为位流
        std::string bitStream;
        uint8_t byte;
        while (in.read(reinterpret_cast<char*>(&byte), 1)) {
            bitStream += std::bitset<8>(byte).to_string();
        }
        in.close();

        // 去除填充位
        if (pad != 8 && bitStream.size() >= pad) {
            bitStream = bitStream.substr(0, bitStream.size() - pad);
        }

        // 解码并写入文件
        std::ofstream out(outputPath, std::ios::binary);
        if (!out) {
            std::cerr << "错误：无法创建输出文件 " << outputPath << std::endl;
            return false;
        }

        std::string currentCode;
        for (char bit : bitStream) {
            currentCode += bit;
            if (codeMap.count(currentCode)) {
                out.put(static_cast<char>(codeMap[currentCode]));
                currentCode.clear();
            }
        }

        out.close();
        std::cout << "单文件解压完成：" << outputPath << std::endl;
        return true;
    }
};

// 多文件压缩/解压实现类
class MultiFileCompressor : public ICompressor {
public:
    std::unordered_map<uint8_t, std::string> globalCodes;    // 全局编码表（压缩用）
    std::unordered_map<std::string, uint8_t> globalCodeMap; // 全局反向编码表（解压用）

    // 构建哈夫曼树
    Node* buildTree(std::unordered_map<uint8_t, int>& freq) {
        std::priority_queue<Node*, std::vector<Node*>, CompareNode> minHeap;
        for (const auto& p : freq) {
            minHeap.push(new Node(p.first, p.second));
        }

        while (minHeap.size() > 1) {
            auto left = minHeap.top(); minHeap.pop();
            auto right = minHeap.top(); minHeap.pop();
            minHeap.push(new Node(left, right));
        }

        return minHeap.empty() ? nullptr : minHeap.top();
    }

    // 生成全局编码表
    void generateGlobalCodes(Node* root, std::string code) {
        if (!root) return;
        if (!root->left && !root->right) {
            globalCodes[root->data] = code.empty() ? "0" : code;
            globalCodeMap[code.empty() ? "0" : code] = root->data;
            return;
        }
        generateGlobalCodes(root->left, code + "0");
        generateGlobalCodes(root->right, code + "1");
    }

    // 统计多文件全局字节频率
    std::unordered_map<uint8_t, int> countGlobalFreq(const std::vector<std::pair<std::string, std::string>>& fileList) {
        std::unordered_map<uint8_t, int> freqMap;
        const DWORD BUF_SIZE = 4096;
        uint8_t buf[BUF_SIZE];
        DWORD bytesRead;

        for (const auto& [relPath, absPath] : fileList) {
            HANDLE hFile = CreateFileA(absPath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL,
                OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
            if (hFile == INVALID_HANDLE_VALUE) {
                std::cerr << "警告：跳过无法读取的文件 " << relPath << "（错误码：" << GetLastError() << "）" << std::endl;
                continue;
            }

            while (ReadFile(hFile, buf, BUF_SIZE, &bytesRead, NULL) && bytesRead > 0) {
                for (DWORD i = 0; i < bytesRead; ++i) {
                    freqMap[buf[i]]++;
                }
            }
            CloseHandle(hFile);
        }
        return freqMap;
    }

    // 单个文件按全局编码表压缩为字节流
    std::vector<uint8_t> compressFileByGlobalCode(const std::string& filePath) {
        std::vector<uint8_t> compressedData;
        std::string bitStream;
        const DWORD BUF_SIZE = 4096;
        uint8_t buf[BUF_SIZE];
        DWORD bytesRead;

        HANDLE hFile = CreateFileA(filePath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL,
            OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE) {
            std::cerr << "错误：无法读取文件 " << filePath << "（错误码：" << GetLastError() << "）" << std::endl;
            return compressedData;
        }

        while (ReadFile(hFile, buf, BUF_SIZE, &bytesRead, NULL) && bytesRead > 0) {
            for (DWORD i = 0; i < bytesRead; ++i) {
                auto iter = globalCodes.find(buf[i]);
                if (iter != globalCodes.end()) {
                    bitStream += iter->second;
                }
            }
        }
        CloseHandle(hFile);

        // 处理填充位
        uint8_t padBits = 8 - (bitStream.size() % 8);
        if (padBits != 8) {
            bitStream += std::string(padBits, '0');
        }
        compressedData.push_back(padBits);

        // 位流转字节流
        for (size_t i = 0; i < bitStream.size(); i += 8) {
            std::string byteStr = bitStream.substr(i, 8);
            std::bitset<8> bits(byteStr);
            compressedData.push_back(static_cast<uint8_t>(bits.to_ulong()));
        }

        return compressedData;
    }

    // 写入压缩包头部（标识+文件数+全局编码表）
    bool writeArchiveHeader(std::ofstream& outArchive, uint32_t fileCount) {
        // 写入压缩标识（1=多文件）
        uint8_t archiveType = 1;
        outArchive.write(reinterpret_cast<const char*>(&archiveType), sizeof(archiveType));

        // 写入文件总数
        outArchive.write(reinterpret_cast<const char*>(&fileCount), sizeof(fileCount));

        // 写入编码表大小
        uint32_t codeCount = globalCodes.size();
        outArchive.write(reinterpret_cast<const char*>(&codeCount), sizeof(codeCount));

        // 写入每个编码条目
        for (const auto& [byte, code] : globalCodes) {
            outArchive.write(reinterpret_cast<const char*>(&byte), sizeof(byte));
            uint32_t codeLen = code.size();
            outArchive.write(reinterpret_cast<const char*>(&codeLen), sizeof(codeLen));

            // 编码内容位打包
            std::string codeBitStream = code;
            uint8_t pad = 8 - (codeBitStream.size() % 8);
            if (pad != 8) codeBitStream += std::string(pad, '0');
            outArchive.write(reinterpret_cast<const char*>(&pad), sizeof(pad));

            for (size_t i = 0; i < codeBitStream.size(); i += 8) {
                std::bitset<8> bits(codeBitStream.substr(i, 8));
                uint8_t codeByte = static_cast<uint8_t>(bits.to_ulong());
                outArchive.write(reinterpret_cast<const char*>(&codeByte), sizeof(codeByte));
            }
        }

        return !outArchive.fail();
    }

    // 读取压缩包头部（解析编码表和文件数）
    bool readArchiveHeader(std::ifstream& inArchive, uint32_t& fileCount) {
        // 读取压缩标识
        uint8_t archiveType;
        inArchive.read(reinterpret_cast<char*>(&archiveType), sizeof(archiveType));
        if (archiveType != 1) {
            std::cerr << "错误：不支持的压缩包类型（仅支持多文件）" << std::endl;
            return false;
        }

        // 读取文件总数
        inArchive.read(reinterpret_cast<char*>(&fileCount), sizeof(fileCount));

        // 读取编码表大小
        uint32_t codeCount;
        inArchive.read(reinterpret_cast<char*>(&codeCount), sizeof(codeCount));

        // 解析编码表
        globalCodes.clear();
        globalCodeMap.clear();
        for (uint32_t i = 0; i < codeCount; ++i) {
            uint8_t byte;
            inArchive.read(reinterpret_cast<char*>(&byte), sizeof(byte));

            uint32_t codeLen;
            inArchive.read(reinterpret_cast<char*>(&codeLen), sizeof(codeLen));

            uint8_t codePad;
            inArchive.read(reinterpret_cast<char*>(&codePad), sizeof(codePad));

            uint32_t codeByteCount = (codeLen + 7) / 8;
            std::vector<uint8_t> codeBytes(codeByteCount);
            inArchive.read(reinterpret_cast<char*>(codeBytes.data()), codeByteCount);

            // 还原编码字符串
            std::string codeStr;
            for (uint8_t b : codeBytes) {
                codeStr += std::bitset<8>(b).to_string();
            }
            if (codePad != 8 && codeStr.size() >= codePad) {
                codeStr = codeStr.substr(0, codeStr.size() - codePad);
            }
            codeStr = codeStr.substr(0, codeLen);

            globalCodes[byte] = codeStr;
            globalCodeMap[codeStr] = byte;
        }

        return !inArchive.fail();
    }

    // 单个文件按全局编码表解压
    bool decompressSingleFile(const std::vector<uint8_t>& compressedData, uint64_t originalSize, const std::string& outputPath) {
        if (originalSize == 0) {
            std::ofstream outFile(outputPath, std::ios::binary);
            outFile.close();
            return true;
        }

        // 提取填充位和位流
        uint8_t dataPad = compressedData[0];
        std::string bitStream;
        for (size_t i = 1; i < compressedData.size(); ++i) {
            bitStream += std::bitset<8>(compressedData[i]).to_string();
        }

        if (dataPad != 8 && bitStream.size() >= dataPad) {
            bitStream = bitStream.substr(0, bitStream.size() - dataPad);
        }

        // 解码写入文件
        std::ofstream outFile(outputPath, std::ios::binary);
        if (!outFile) {
            std::cerr << "错误：无法创建文件 " << outputPath << std::endl;
            return false;
        }

        const size_t BUF_SIZE = 4096;
        uint8_t writeBuf[BUF_SIZE];
        size_t bufIdx = 0;
        uint64_t writtenBytes = 0;
        std::string currentCode;

        for (char bit : bitStream) {
            currentCode += bit;
            auto iter = globalCodeMap.find(currentCode);
            if (iter != globalCodeMap.end()) {
                writeBuf[bufIdx++] = iter->second;
                writtenBytes++;
                currentCode.clear();

                if (bufIdx == BUF_SIZE || writtenBytes == originalSize) {
                    outFile.write(reinterpret_cast<char*>(writeBuf), bufIdx);
                    bufIdx = 0;
                }

                if (writtenBytes == originalSize) break;
            }
        }

        outFile.close();
        return writtenBytes == originalSize;
    }

public:
    // 实现抽象接口：多文件压缩（inputPath为文件列表字符串，用逗号分隔）
    bool compress(const std::string& inputFileList, const std::string& outputPath) override {
        // 解析输入文件列表（格式："file1.txt,file2.png,..."）
        std::vector<std::string> inputFiles;
        size_t pos = 0;
        while (pos < inputFileList.size()) {
            size_t commaPos = inputFileList.find(',', pos);
            if (commaPos == std::string::npos) {
                inputFiles.push_back(inputFileList.substr(pos));
                break;
            }
            inputFiles.push_back(inputFileList.substr(pos, commaPos - pos));
            pos = commaPos + 1;
        }

        if (inputFiles.empty()) {
            std::cerr << "错误：无待压缩文件" << std::endl;
            return false;
        }

        // 收集有效文件列表（相对路径+绝对路径）
        std::vector<std::pair<std::string, std::string>> fileList;
        for (const std::string& filePath : inputFiles) {
            if (!FileUtils::pathExists(filePath)) {
                std::cerr << "警告：文件不存在 " << filePath << "，跳过" << std::endl;
                continue;
            }
            if (FileUtils::isDirectory(filePath)) {
                std::cerr << "警告：" << filePath << " 是目录，多文件压缩仅支持文件" << std::endl;
                continue;
            }

            // 提取相对路径（文件名）
            size_t slashPos = filePath.find_last_of("\\/");
            std::string fileName = (slashPos == std::string::npos) ? filePath : filePath.substr(slashPos + 1);
            fileList.emplace_back(fileName, filePath);
        }

        if (fileList.empty()) {
            std::cerr << "错误：无有效待压缩文件" << std::endl;
            return false;
        }

        // 生成全局频率表和编码表
        std::cout << "正在统计全局文件频率..." << std::endl;
        auto globalFreq = countGlobalFreq(fileList);
        auto root = buildTree(globalFreq);
        globalCodes.clear();
        globalCodeMap.clear();
        generateGlobalCodes(root, "");
        delete root;

        // 创建压缩包并写入头部
        std::ofstream outArchive(outputPath, std::ios::binary);
        if (!outArchive) {
            std::cerr << "错误：无法创建压缩包 " << outputPath << std::endl;
            return false;
        }

        if (!writeArchiveHeader(outArchive, fileList.size())) {
            std::cerr << "错误：写入压缩包头部失败" << std::endl;
            outArchive.close();
            return false;
        }

        // 逐个文件压缩并写入
        for (const auto& [relPath, absPath] : fileList) {
            std::cout << "正在压缩：" << relPath << "（大小：" << FileUtils::getFileSize(absPath) << "B）" << std::endl;

            // 写入文件元信息
            uint32_t pathLen = relPath.size();
            outArchive.write(reinterpret_cast<char*>(&pathLen), sizeof(pathLen));
            outArchive.write(relPath.c_str(), pathLen);

            uint64_t originalSize = FileUtils::getFileSize(absPath);
            outArchive.write(reinterpret_cast<char*>(&originalSize), sizeof(originalSize));

            // 压缩文件内容并写入
            std::vector<uint8_t> compressedData = compressFileByGlobalCode(absPath);
            uint64_t dataSize = compressedData.size();
            outArchive.write(reinterpret_cast<char*>(&dataSize), sizeof(dataSize));
            outArchive.write(reinterpret_cast<const char*>(compressedData.data()), dataSize);
        }

        outArchive.close();
        std::cout << "多文件压缩完成：" << outputPath << std::endl;
        return true;
    }

    // 实现抽象接口：多文件解压（outputPath为输出目录）
    bool decompress(const std::string& inputPath, const std::string& outputDir) override {
        // 验证输入输出路径
        if (!FileUtils::pathExists(inputPath)) {
            std::cerr << "错误：压缩包不存在 " << inputPath << std::endl;
            return false;
        }

        if (!FileUtils::createDirRecursive(outputDir)) {
            std::cerr << "错误：无法创建输出目录 " << outputDir << std::endl;
            return false;
        }

        // 打开压缩包并读取头部
        std::ifstream inArchive(inputPath, std::ios::binary);
        if (!inArchive) {
            std::cerr << "错误：无法打开压缩包 " << inputPath << std::endl;
            return false;
        }

        uint32_t fileCount;
        if (!readArchiveHeader(inArchive, fileCount)) {
            std::cerr << "错误：读取压缩包头部失败" << std::endl;
            inArchive.close();
            return false;
        }

        std::cout << "压缩包包含 " << fileCount << " 个文件，开始解压..." << std::endl;

        // 逐个文件解压
        for (uint32_t i = 0; i < fileCount; ++i) {
            // 读取文件元信息
            uint32_t pathLen;
            if (!inArchive.read(reinterpret_cast<char*>(&pathLen), sizeof(pathLen))) {
                std::cerr << "警告：压缩包损坏，无法读取第 " << i + 1 << " 个文件路径长度" << std::endl;
                break;
            }

            std::string relPath(pathLen, 0);
            if (!inArchive.read(&relPath[0], pathLen)) {
                std::cerr << "警告：压缩包损坏，无法读取第 " << i + 1 << " 个文件路径" << std::endl;
                break;
            }

            uint64_t originalSize;
            if (!inArchive.read(reinterpret_cast<char*>(&originalSize), sizeof(originalSize))) {
                std::cerr << "警告：压缩包损坏，无法读取第 " << i + 1 << " 个文件原始大小" << std::endl;
                break;
            }

            uint64_t compressedDataSize;
            if (!inArchive.read(reinterpret_cast<char*>(&compressedDataSize), sizeof(compressedDataSize))) {
                std::cerr << "警告：压缩包损坏，无法读取第 " << i + 1 << " 个文件压缩数据大小" << std::endl;
                break;
            }

            // 读取压缩数据
            std::vector<uint8_t> compressedData(compressedDataSize);
            if (!inArchive.read(reinterpret_cast<char*>(compressedData.data()), compressedDataSize)) {
                std::cerr << "警告：压缩包损坏，无法读取第 " << i + 1 << " 个文件压缩数据" << std::endl;
                break;
            }

            // 生成输出路径并创建父目录
            std::string outputPath = outputDir + "\\" + relPath;
            size_t lastSlash = outputPath.find_last_of("\\");
            if (lastSlash != std::string::npos) {
                std::string parentDir = outputPath.substr(0, lastSlash);
                if (!FileUtils::createDirRecursive(parentDir)) {
                    std::cerr << "警告：无法创建父目录 " << parentDir << "，跳过文件 " << relPath << std::endl;
                    continue;
                }
            }

            // 解压单个文件
            std::cout << "正在解压：" << relPath << std::endl;
            if (decompressSingleFile(compressedData, originalSize, outputPath)) {
                std::cout << "解压成功：" << relPath << std::endl;
            }
            else {
                std::cerr << "警告：解压失败 " << relPath << std::endl;
            }
        }

        inArchive.close();
        std::cout << "多文件解压完成！输出目录：" << outputDir << std::endl;
        return true;
    }
};

// 文件夹压缩/解压实现类（继承多文件压缩逻辑，扩展文件夹遍历）
class FolderCompressor : public MultiFileCompressor {
private:
    // 递归遍历文件夹，收集所有文件的【相对路径+绝对路径】
    void traverseFolder(const std::string& rootDir, const std::string& currentDir,
        std::vector<std::pair<std::string, std::string>>& fileList) {
        // 构建当前目录的完整路径（如 rootDir=E:\test，currentDir=subdir → E:\test\subdir\*）
        std::string searchPath = rootDir;
        if (!currentDir.empty()) {
            searchPath += "\\";
            searchPath += currentDir;
        }
        searchPath += "\\*";  // 匹配所有文件/目录

        // Windows API：遍历目录
        WIN32_FIND_DATAA findData;
        HANDLE hFind = FindFirstFileA(searchPath.c_str(), &findData);
        if (hFind == INVALID_HANDLE_VALUE) {
            std::cerr << "警告：无法遍历目录 " << searchPath << "（错误码：" << GetLastError() << "）" << std::endl;
            return;
        }

        do {
            std::string fileName = findData.cFileName;
            // 跳过当前目录（.）和上级目录（..）
            if (fileName == "." || fileName == "..") {
                continue;
            }

            // 构建相对路径和绝对路径
            std::string relPath = currentDir.empty() ? fileName : currentDir + "\\" + fileName;
            std::string absPath = rootDir + "\\" + relPath;

            // 判断是否为目录：若是则递归遍历，否则加入文件列表
            if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                traverseFolder(rootDir, relPath, fileList);  // 递归处理子目录
            }
            else {
                fileList.emplace_back(relPath, absPath);  // 收集文件信息
            }
        } while (FindNextFileA(hFind, &findData));

        FindClose(hFind);  // 关闭目录句柄，避免资源泄漏
    }

public:
    // 实现抽象接口：文件夹压缩（inputPath=目标文件夹路径，outputPath=压缩包路径）
    bool compress(const std::string& inputFolderPath, const std::string& outputArchive) override {
        // 1. 验证输入文件夹路径
        if (!FileUtils::pathExists(inputFolderPath)) {
            std::cerr << "错误：文件夹不存在 " << inputFolderPath << std::endl;
            return false;
        }
        if (!FileUtils::isDirectory(inputFolderPath)) {
            std::cerr << "错误：输入路径不是文件夹 " << inputFolderPath << std::endl;
            return false;
        }

        // 2. 递归遍历文件夹，收集所有文件列表
        std::vector<std::pair<std::string, std::string>> fileList;
        std::cout << "正在扫描文件夹：" << inputFolderPath << std::endl;
        traverseFolder(inputFolderPath, "", fileList);  // currentDir为空表示从根目录开始

        // 3. 无有效文件处理
        if (fileList.empty()) {
            std::cerr << "警告：文件夹 " << inputFolderPath << " 中无有效文件" << std::endl;
            // 仍创建空压缩包（符合压缩工具惯例）
            std::ofstream outArchive(outputArchive, std::ios::binary);
            outArchive.close();
            std::cout << "已创建空压缩包：" << outputArchive << std::endl;
            return true;
        }

        std::cout << "共扫描到 " << fileList.size() << " 个文件" << std::endl;

        // 4. 复用多文件压缩的核心逻辑（生成全局编码表+写入压缩包）
        // 4.1 统计全局频率
        std::cout << "正在统计全局文件频率..." << std::endl;
        auto globalFreq = countGlobalFreq(fileList);  // 继承自 MultiFileCompressor
        auto root = buildTree(globalFreq);            // 继承自 MultiFileCompressor
        globalCodes.clear();
        globalCodeMap.clear();
        generateGlobalCodes(root, "");               // 继承自 MultiFileCompressor
        delete root;

        // 4.2 创建压缩包并写入头部
        std::ofstream outArchive(outputArchive, std::ios::binary);
        if (!outArchive) {
            std::cerr << "错误：无法创建压缩包 " << outputArchive << std::endl;
            return false;
        }

        if (!writeArchiveHeader(outArchive, fileList.size())) {  // 继承自 MultiFileCompressor
            std::cerr << "错误：写入压缩包头部失败" << std::endl;
            outArchive.close();
            return false;
        }

        // 4.3 逐个文件压缩并写入压缩包
        for (const auto& [relPath, absPath] : fileList) {
            std::cout << "正在压缩：" << relPath << "（大小：" << FileUtils::getFileSize(absPath) << "B）" << std::endl;

            // 写入文件元信息（相对路径+原始大小）
            uint32_t pathLen = relPath.size();
            outArchive.write(reinterpret_cast<char*>(&pathLen), sizeof(pathLen));
            outArchive.write(relPath.c_str(), pathLen);

            uint64_t originalSize = FileUtils::getFileSize(absPath);
            outArchive.write(reinterpret_cast<char*>(&originalSize), sizeof(originalSize));

            // 压缩文件内容并写入
            std::vector<uint8_t> compressedData = compressFileByGlobalCode(absPath);  // 继承自 MultiFileCompressor
            uint64_t dataSize = compressedData.size();
            outArchive.write(reinterpret_cast<char*>(&dataSize), sizeof(dataSize));
            outArchive.write(reinterpret_cast<const char*>(compressedData.data()), dataSize);
        }

        outArchive.close();
        std::cout << "文件夹压缩完成！压缩包：" << outputArchive << std::endl;
        return true;
    }

    // 实现抽象接口：文件夹解压（复用多文件解压逻辑，无需额外修改）
    bool decompress(const std::string& inputArchive, const std::string& outputFolder) override {
        std::cout << "正在解压文件夹压缩包：" << inputArchive << std::endl;
        // 直接复用 MultiFileCompressor 的解压逻辑（自动还原目录结构）
        return MultiFileCompressor::decompress(inputArchive, outputFolder);
    }
};