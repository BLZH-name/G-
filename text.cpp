//
//#include<iostream>
//#include<fstream>
//#include <bitset>
//#include<vector>
//#include<string>
//#include <unordered_map>
//#include<queue>
//#include<io.h>
//#include<algorithm>
//#include<windows.h>  
//
////为什么不写 using namespace std来进行减少工作量？
////因为 c++17版本下， 引用widows.h文件可能会导致byte引用错误
//
//
//
//struct Node {//用于处理哈夫曼树和哈夫曼节点
//	uint8_t data;
//	int freq;
//	Node* left;
//	Node* right;
//	Node(char c, int t) :data(c), freq(t), left(nullptr), right(nullptr) {}
//	Node(Node* l, Node* r) :data(0), freq(l->freq + r->freq), left(l), right(r) {}
//};
//
//struct CompareNode {
//	bool operator()(Node* a, Node* b) {
//		return a->freq > b->freq;
//	}
//};
//
//class Hufuman {
//private:
//	std::unordered_map<uint8_t, std::string> globalCodes;  // 全局编码，压缩用
//	std::unordered_map<std::string, uint8_t> unzip;//解压要用到的工具
//	std::unordered_map<std::string, uint8_t> globalUnzip;//解压全局反向编码
//
//
//
////多文件处理方案：
//private:
//	//创建目录
//	bool createDirRecursive(const std::string& dirPath) const {
//		std::string winPath = dirPath;
//		std::replace(winPath.begin(), winPath.end(), '/', '\\');  // 统一为Windows路径分隔符
//
//		// 处理根路径（如 C:\）
//		if (winPath.size() >= 2 && winPath[1] == ':') {
//			if (winPath.size() == 2 || (winPath.size() == 3 && winPath[2] == '\\')) {
//				return true;  // 根路径已存在
//			}
//		}
//		// 逐段创建目录
//		size_t pos = 0;
//		while ((pos = winPath.find('\\', pos + 1)) != std::string::npos) {
//			std::string subDir = winPath.substr(0, pos);
//			if (!pathExists(subDir)) {
//				if (!CreateDirectoryA(subDir.c_str(), NULL)) {
//					DWORD err = GetLastError();
//					if (err != ERROR_ALREADY_EXISTS) {
//						std::cerr << "警告：创建目录失败 " << subDir << "（错误码：" << err << "）" << std::endl;
//						return false;
//					}
//				}
//			}
//		}
//
//		// 创建最后一级目录
//		if (!pathExists(winPath)) {
//			if (!CreateDirectoryA(winPath.c_str(), NULL)) {
//				DWORD err = GetLastError();
//				if (err != ERROR_ALREADY_EXISTS) {
//					std::cerr << "警告：创建目录失败 " << winPath << "（错误码：" << err << "）" << std::endl;
//					return false;
//				}
//			}
//		}
//		return true;
//	}
////111
//private:
//	// 读取压缩包头部：解析标识+文件数+全局编码表，重建反向编码表
//	bool readArchiveHeader(std::ifstream& inArchive, uint32_t& fileCount) {
//		// 1. 读取压缩标识（必须为1，否则不是多文件压缩包）
//		uint8_t archiveType;
//		inArchive.read(reinterpret_cast<char*>(&archiveType), sizeof(archiveType));
//		if (archiveType != 1) {
//			std::cerr << "错误：不支持的压缩包类型（仅支持多文件压缩包）" << std::endl;
//			return false;
//		}
//
//		// 2. 读取文件总数（知道要解压多少个文件）
//		inArchive.read(reinterpret_cast<char*>(&fileCount), sizeof(fileCount));
//
//		// 3. 读取全局编码表大小（编码表条目数量）
//		uint32_t codeCount;
//		inArchive.read(reinterpret_cast<char*>(&codeCount), sizeof(codeCount));
//
//		// 4. 逐个解析编码条目，重建全局编码表和反向编码表
//		globalCodes.clear();
//		globalUnzip.clear();
//		for (uint32_t i = 0; i < codeCount; ++i) {
//			// 4.1 读取字节值（如 97 对应 'a'）
//			uint8_t dataByte;
//			inArchive.read(reinterpret_cast<char*>(&dataByte), sizeof(dataByte));
//
//			// 4.2 读取编码长度（如 "01" 的长度为2）
//			uint32_t codeLen;
//			inArchive.read(reinterpret_cast<char*>(&codeLen), sizeof(codeLen));
//
//			// 4.3 读取编码内容的填充位（压缩时补的0，解压时需去除）
//			uint8_t codePad;
//			inArchive.read(reinterpret_cast<char*>(&codePad), sizeof(codePad));
//
//			// 4.4 读取编码内容的字节流，还原为编码字符串
//			uint32_t codeByteCount = (codeLen + 7) / 8;  // 编码占用的字节数
//			std::vector<uint8_t> codeBytes(codeByteCount);
//			inArchive.read(reinterpret_cast<char*>(codeBytes.data()), codeByteCount);
//
//			// 还原编码字符串（字节→8位二进制字符串，去除填充位）
//			std::string codeStr;
//			for (uint8_t b : codeBytes) {
//				codeStr += std::bitset<8>(b).to_string();
//			}
//			// 去掉编码内容的填充位
//			if (codePad != 8 && codeStr.size() >= codePad) {
//				codeStr = codeStr.substr(0, codeStr.size() - codePad);
//			}
//			// 截取真实编码长度（避免多余字符）
//			codeStr = codeStr.substr(0, codeLen);
//
//			// 存储编码表和反向编码表
//			globalCodes[dataByte] = codeStr;
//			globalUnzip[codeStr] = dataByte;
//		}
//
//		return !inArchive.fail();  // 返回读取是否成功
//	}
//
////112
//	private:
//		// 单个文件解压：compressedData=压缩数据，originalSize=原始大小，outputPath=输出路径
//		bool decompressSingleFile(const std::vector<uint8_t>& compressedData,
//			uint64_t originalSize, const std::string& outputPath) const {
//			// 处理空文件（直接创建空文件）
//			if (originalSize == 0) {
//				std::ofstream outFile(outputPath, std::ios::binary);
//				outFile.close();
//				return true;
//			}
//
//			// 1. 提取压缩数据中的填充位（压缩时补的0，解压时需去除）
//			uint8_t dataPad = compressedData[0];
//			std::string bitStream;
//
//			// 2. 压缩数据→二进制位流（跳过填充位标识字节）
//			for (size_t i = 1; i < compressedData.size(); ++i) {
//				bitStream += std::bitset<8>(compressedData[i]).to_string();
//			}
//
//			// 3. 去除填充位，恢复原始编码位流
//			if (dataPad != 8 && bitStream.size() >= dataPad) {
//				bitStream = bitStream.substr(0, bitStream.size() - dataPad);
//			}
//
//			// 4. 用全局反向编码表解码（编码→字节）
//			std::ofstream outFile(outputPath, std::ios::binary);
//			if (!outFile) {
//				std::cerr << "错误：无法创建文件 " << outputPath << std::endl;
//				return false;
//			}
//
//			const size_t BUF_SIZE = 4096;  // 4KB缓冲区，提升写入效率
//			uint8_t writeBuf[BUF_SIZE];
//			size_t bufIdx = 0;
//			uint64_t writtenBytes = 0;
//			std::string currentCode;
//
//			for (char bit : bitStream) {
//				currentCode += bit;
//				// 匹配到编码，还原为字节
//				auto iter = globalUnzip.find(currentCode);
//				if (iter != globalUnzip.end()) {
//					writeBuf[bufIdx++] = iter->second;
//					writtenBytes++;
//					currentCode.clear();
//
//					// 缓冲区满或达到原始大小，写入文件
//					if (bufIdx == BUF_SIZE || writtenBytes == originalSize) {
//						outFile.write(reinterpret_cast<char*>(writeBuf), bufIdx);
//						bufIdx = 0;
//					}
//
//					// 达到原始大小，停止解码（避免多余数据）
//					if (writtenBytes == originalSize) {
//						break;
//					}
//				}
//			}
//
//			outFile.close();
//			// 验证解压完整性（写入字节数=原始大小）
//			return writtenBytes == originalSize;
//		}
////113
//
//
//
//
//
//	std::unordered_map<uint8_t, int> countfreq(std::string inpath) {//读取数据
//		std::unordered_map<uint8_t, int>freq;
//		std::ifstream in(inpath, std::ios::binary);
//		if (!in) {
//			std::cout << "读取失败" << std::endl; exit(1);
//		}
//		char c;
//		while (in.read((char*)&c, 1)) freq[c]++;
//		in.close();
//		return freq;
//	}
//
//
////一
//	uint64_t getFileSize(const std::string& filePath) const {
//		// 打开文件（只读模式，共享读权限）
//		HANDLE hFile = CreateFileA(filePath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL,
//			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
//		if (hFile == INVALID_HANDLE_VALUE) {
//			std::cerr << "警告：无法打开文件 " << filePath << "（错误码：" << GetLastError() << "）" << std::endl;
//			return 0;
//		}
//
//		// 获取文件大小（分低32位和高32位，支持大文件）
//		DWORD lowSize = GetFileSize(hFile, NULL);
//		DWORD highSize = 0;//DWORD是无符号32位整形
//		if (lowSize == INVALID_FILE_SIZE && GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
//			highSize = GetFileSize(hFile, &lowSize);  // 处理>4GB文件
//		}
//		CloseHandle(hFile);//关闭文件句柄
//
//		// 合并高低位，返回64位文件大小
//		return (static_cast<uint64_t>(highSize) << 32) | lowSize;
//	}
//
//	// 2. 判断路径是否为目录（避免将目录当作文件压缩）
//	bool isDirectory(const std::string& path) const {
//		DWORD attr = GetFileAttributesA(path.c_str());  // 获取路径属性
//		if (attr == INVALID_FILE_ATTRIBUTES) return false;
//		return (attr & FILE_ATTRIBUTE_DIRECTORY) != 0;  // 目录属性判断
//	}
//
//	// 3. 判断路径是否存在（过滤无效文件）
//	bool pathExists(const std::string& path) const {
//		DWORD attr = GetFileAttributesA(path.c_str());
//		return attr != INVALID_FILE_ATTRIBUTES;  // 属性有效则路径存在
//	}
//
////二	
//	// 统计多文件的全局字节频率（遍历所有文件，累计每个字节的出现次数）
//	std::unordered_map<uint8_t, int> countGlobalFrequency(const std::vector< std::pair<std::string, std::string>>& fileList) const {
//		std::unordered_map<uint8_t, int> freqMap;  // key：字节（0-255），value：全局总频率
//		const DWORD BUF_SIZE = 4096;         // 4KB缓冲区，减少IO次数（提升效率）
//		uint8_t buf[BUF_SIZE];
//		DWORD bytesRead;                     // 每次实际读取的字节数
//
//		// 遍历每个文件
//		for (const auto& [relPath, absPath] : fileList) {
//			// 打开文件（Windows API：CreateFileA）
//			HANDLE hFile = CreateFileA(absPath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL,
//				OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
//			if (hFile == INVALID_HANDLE_VALUE) {
//				std::cerr << "警告：跳过无法读取的文件 " << relPath << "（错误码：" << GetLastError() << "）" << std::endl;
//				continue;
//			}
//
//			// 批量读取文件内容（4KB/次）
//			while (ReadFile(hFile, buf, BUF_SIZE, &bytesRead, NULL) && bytesRead > 0) {
//				// 累计每个字节的频率
//				for (DWORD i = 0; i < bytesRead; ++i) {
//					freqMap[buf[i]]++;
//				}
//			}
//
//			CloseHandle(hFile);  // 关闭文件句柄，避免资源泄漏
//		}
//		return freqMap;
//	}
//
////三
//
//	// 单个文件按全局编码表压缩为字节流（返回压缩后的数据，供后续写入压缩包）
//	std::vector<uint8_t> compressFileByGlobalCode(const std::string& filePath) const {
//		 std::vector<uint8_t> compressedData;  // 存储压缩后的数据（填充位+编码字节流）
//		std::string bitStream;                // 存储编码后的二进制位流（如"01101001..."）
//		const DWORD BUF_SIZE = 4096;     // 4KB缓冲区，提升读取效率
//		uint8_t buf[BUF_SIZE];
//		DWORD bytesRead;
//
//		// 打开文件（只读模式）
//		HANDLE hFile = CreateFileA(filePath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL,
//			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
//		if (hFile == INVALID_HANDLE_VALUE) {
//			std::cerr << "错误：无法读取文件 " << filePath << "（错误码：" << GetLastError() << "）" << std::endl;
//			return compressedData;
//		}
//
//		// 读取文件内容，生成编码位流
//		while (ReadFile(hFile, buf, BUF_SIZE, &bytesRead, NULL) && bytesRead > 0) {
//			for (DWORD i = 0; i < bytesRead; ++i) {
//				// 用全局编码表替换字节（避免每个文件单独生成编码表）
//				auto iter = globalCodes.find(buf[i]);
//				if (iter != globalCodes.end()) {
//					bitStream += iter->second;  // 字节→编码字符串（如 97→"01"）
//				}
//			}
//		}
//		CloseHandle(hFile);  // 关闭文件
//
//		// 处理填充位：确保位流长度是8的倍数（磁盘存储最小单位是字节）
//		uint8_t padBits = 8 - (bitStream.size() % 8);
//		if (padBits != 8) {  // 若长度不是8的倍数，补0
//			bitStream += std::string(padBits, '0');
//		}
//		compressedData.push_back(padBits);  // 存储填充位数（解压时需去除补的0）
//
//		// 位流→字节流（8位=1字节，便于存储）
//		for (size_t i = 0; i < bitStream.size(); i += 8) {
//			std::string byteStr = bitStream.substr(i, 8);  // 每次取8位
//			std::bitset<8> bits(byteStr);                  // 转换为8位二进制
//			compressedData.push_back(static_cast<uint8_t>(bits.to_ulong()));  // 转换为字节
//		}
//
//		return compressedData;
//	}
//
////四
//
//		// 写入压缩包头部（标识+文件数+全局编码表）
//		bool writeArchiveHeader(std::ofstream& outArchive, uint32_t fileCount) const {
//			// 1. 写入压缩标识（1字节）：1=多文件/文件夹，0=单文件（用于解压时判断类型）
//			uint8_t archiveType = 1;
//			outArchive.write(reinterpret_cast<const char*>(&archiveType), sizeof(archiveType));
//
//			// 2. 写入文件总数（4字节）：告诉解压程序要处理多少个文件
//			outArchive.write(reinterpret_cast<const char*>(&fileCount), sizeof(fileCount));
//
//			// 3. 写入全局编码表大小（4字节）：编码表中有多少个字节的编码（如256个）
//			uint32_t codeCount = globalCodes.size();
//			outArchive.write(reinterpret_cast<const char*>(&codeCount), sizeof(codeCount));
//
//			// 4. 写入每个编码条目（字节+编码长度+编码内容）：解压时重建编码表
//			for (const auto& [ret, code] : globalCodes) {
//				// 4.1 写入字节值（1字节）：如 97（对应字符'a'）
//				outArchive.write(reinterpret_cast<const char*>(&ret), sizeof(ret));
//
//				// 4.2 写入编码长度（4字节）：如 "01" 的长度是2
//				uint32_t codeLen = code.size();
//				outArchive.write(reinterpret_cast<const char*>(&codeLen), sizeof(codeLen));
//
//				// 4.3 写入编码内容（位打包为字节）：避免编码字符串直接存储的冗余
//				std::string codeBitStream = code;
//				uint8_t pad = 8 - (codeBitStream.size() % 8);  // 编码内容的填充位
//				if (pad != 8) codeBitStream += std::string(pad, '0');
//				outArchive.write(reinterpret_cast<const char*>(&pad), sizeof(pad));  // 存储编码的填充位数
//
//				// 4.4 写入编码内容的字节流
//				for (size_t i = 0; i < codeBitStream.size(); i += 8) {
//					std::bitset<8> bits(codeBitStream.substr(i, 8));
//					uint8_t codeByte = static_cast<uint8_t>(bits.to_ulong());
//					outArchive.write(reinterpret_cast<const char*>(&codeByte), sizeof(codeByte));
//				}
//			}
//
//			return !outArchive.fail();  // 返回是否写入成功
//		}
//
////五
//	public:
//			void decompressMultipleFiles(const std::string& inputArchive, const std::string& outputDir) {
//				// 1. 验证压缩包是否存在
//				if (!pathExists(inputArchive)) {
//					std::cerr << "错误：压缩包不存在 " << inputArchive << std::endl;
//					return;
//				}
//
//				// 2. 创建输出目录（支持多层级）
//				if (!createDirRecursive(outputDir)) {
//					std::cerr << "错误：无法创建输出目录 " << outputDir << std::endl;
//					return;
//				}
//
//				// 3. 打开压缩包（二进制模式读取）
//				std::ifstream inArchive(inputArchive, std::ios::binary);
//				if (!inArchive) {
//					std::cerr << "错误：无法打开压缩包 " << inputArchive << std::endl;
//					return;
//				}
//
//				// 4. 读取头部信息，获取文件总数和全局编码表
//				uint32_t fileCount;
//				if (!readArchiveHeader(inArchive, fileCount)) {
//					std::cerr << "错误：读取压缩包头部失败（压缩包可能损坏）" << std::endl;
//					inArchive.close();
//					return;
//				}
//
//				std::cout << "压缩包包含 " << fileCount << " 个文件，开始解压..." << std::endl;
//
//				// 5. 逐个解压文件
//				for (uint32_t i = 0; i < fileCount; ++i) {
//					// 5.1 读取文件元信息：路径长度→相对路径→原始大小→压缩数据大小
//					uint32_t pathLen;
//					if (!inArchive.read(reinterpret_cast<char*>(&pathLen), sizeof(pathLen))) {
//						std::cerr << "警告：压缩包损坏，无法读取第 " << i + 1 << " 个文件的路径长度" << std::endl;
//						break;
//					}
//
//					// 读取相对路径（如 "test.txt"）
//					std::string relPath(pathLen, 0);
//					if (!inArchive.read(&relPath[0], pathLen)) {
//						std::cerr << "警告：压缩包损坏，无法读取第 " << i + 1 << " 个文件的路径" << std::endl;
//						break;
//					}
//
//					// 读取原始文件大小（用于验证解压完整性）
//					uint64_t originalSize;
//					if (!inArchive.read(reinterpret_cast<char*>(&originalSize), sizeof(originalSize))) {
//						std::cerr << "警告：压缩包损坏，无法读取第 " << i + 1 << " 个文件的原始大小" << std::endl;
//						break;
//					}
//
//					// 读取压缩数据大小（知道要读取多少字节的压缩数据）
//					uint64_t compressedDataSize;
//					if (!inArchive.read(reinterpret_cast<char*>(&compressedDataSize), sizeof(compressedDataSize))) {
//						std::cerr << "警告：压缩包损坏，无法读取第 " << i + 1 << " 个文件的压缩数据大小" << std::endl;
//						break;
//					}
//
//					// 5.2 读取压缩数据
//					std::vector<uint8_t> compressedData(compressedDataSize);
//					if (!inArchive.read(reinterpret_cast<char*>(compressedData.data()), compressedDataSize)) {
//						std::cerr << "警告：压缩包损坏，无法读取第 " << i + 1 << " 个文件的压缩数据" << std::endl;
//						break;
//					}
//
//					// 5.3 生成输出路径（输出目录+相对路径）
//					std::string outputPath = outputDir + "\\" + relPath;
//					// 创建父目录（如 "E:\\output\\subdir"）
//					size_t lastSlash = outputPath.find_last_of("\\");
//					if (lastSlash != std::string::npos) {
//						std::string parentDir = outputPath.substr(0, lastSlash);
//						if (!createDirRecursive(parentDir)) {
//							std::cerr << "警告：无法创建父目录 " << parentDir << "，跳过文件 " << relPath << std::endl;
//							continue;
//						}
//					}
//
//					// 5.4 解压单个文件
//					std::cout << "正在解压：" << relPath << "（目标路径：" << outputPath << "）" << std::endl;
//					if (decompressSingleFile(compressedData, originalSize, outputPath)) {
//						std::cout << "解压成功：" << relPath << std::endl;
//					}
//					else {
//						std::cerr << "警告：解压失败 " << relPath << "（数据可能损坏）" << std::endl;
//					}
//				}
//
//				inArchive.close();
//				std::cout << "多文件解压完成！输出目录：" << outputDir << std::endl;
//			}
//
//			
//
//
//			// 多文件压缩：输入文件列表，输出单个压缩包（核心对外接口）
//		void compressMultipleFiles(const std::vector<std::string>& inputFiles, const std::string& outputArchive) {
//				// 1. 验证输入：无文件则直接返回
//				if (inputFiles.empty()) {
//					std::cerr << "错误：无待压缩文件" << std::endl;
//					return;
//				}
//
//				// 2. 收集有效文件列表（过滤目录和不存在的文件）
//				std::vector<std::pair<std::string, std::string>> fileList;  // <相对路径, 绝对路径>
//				for (const std::string& filePath : inputFiles) {
//					if (!pathExists(filePath)) {
//						std::cerr << "警告：文件不存在 " << filePath << "，跳过" << std::endl;
//						continue;
//					}
//					if (isDirectory(filePath)) {
//						std::cerr << "警告：" << filePath << " 是目录，请使用文件夹压缩接口" << std::endl;
//						continue;
//					}
//					// 提取文件名作为相对路径（如 "E:\\test.txt" → "test.txt"）
//					size_t slashPos = filePath.find_last_of("\\/");
//					std::string fileName = (slashPos == std::string::npos) ? filePath : filePath.substr(slashPos + 1);
//					fileList.emplace_back(fileName, filePath);  // 加入文件列表
//				}
//
//				// 3. 无有效文件则返回
//				if (fileList.empty()) {
//					std::cerr << "错误：无有效待压缩文件" << std::endl;
//					return;
//				}
//
//				// 4. 生成全局频率表和编码表（多文件共用）
//				std::cout << "正在统计全局文件频率..." << std::endl;
//				auto globalFreq = countGlobalFrequency(fileList);  // 模块2：全局频率统计
//				auto root = buildTree(globalFreq);                  // 复用原有函数：构建哈夫曼树
//				globalCodes.clear();                                // 清空旧编码表
//				getcodes(root, "", globalCodes);                    // 复用原有函数：生成全局编码表
//				delete root;                                       // 释放哈夫曼树内存，避免泄漏
//
//				// 5. 创建压缩包并写入头部（模块4：头部包含标识+文件数+编码表）
//				std::ofstream outArchive(outputArchive, std::ios::binary);  // 二进制模式写入（避免文本模式转义）
//				if (!outArchive) {
//					std::cerr << "错误：无法创建压缩包 " << outputArchive << std::endl;
//					return;
//				}
//				if (!writeArchiveHeader(outArchive, fileList.size())) {  // 写入头部
//					std::cerr << "错误：写入压缩包头部失败" << std::endl;
//					outArchive.close();
//					return;
//				}
//
//				// 6. 逐个文件压缩并写入压缩包
//				for (const auto& [relPath, absPath] : fileList) {
//					std::cout << "正在压缩：" << relPath << "（原始大小：" << getFileSize(absPath) << "B）" << std::endl;
//
//					// 6.1 写入文件元信息（路径长度+路径内容+原始大小）：解压时还原文件名和验证大小
//					uint32_t pathLen = relPath.size();  // 相对路径长度（如 "test.txt" 长度为8）
//					outArchive.write(reinterpret_cast<char*>(&pathLen), sizeof(pathLen));
//					outArchive.write(relPath.c_str(), pathLen);  // 相对路径内容（如 "test.txt"）
//
//					uint64_t originalSize = getFileSize(absPath);  // 原始文件大小（解压后验证）
//					outArchive.write(reinterpret_cast<char*>(&originalSize), sizeof(originalSize));
//
//					// 6.2 压缩文件内容（模块3：用全局编码表压缩）
//					std::vector<uint8_t> compressedData = compressFileByGlobalCode(absPath);
//					uint64_t dataSize = compressedData.size();  // 压缩后数据大小（解压时读取对应字节）
//					outArchive.write(reinterpret_cast<char*>(&dataSize), sizeof(dataSize));
//					outArchive.write(reinterpret_cast<const char*>(compressedData.data()), dataSize);
//				}
//
//				// 7. 关闭压缩包，完成压缩
//				outArchive.close();
//				std::cout << "多文件压缩完成！压缩包：" << outputArchive << std::endl;
//			}
//
//		Node* buildTree(std::unordered_map<uint8_t, int>& freq) {//创建哈夫曼树
//				std::priority_queue<Node*, std::vector<Node*>, CompareNode>ret;
//				for (const auto& p : freq) {
//					ret.push(new Node(p.first, p.second));
//				}
//				while (ret.size() > 1) {
//					auto left = ret.top(); ret.pop();
//					auto right = ret.top(); ret.pop();
//					ret.push(new Node(left, right));
//				}
//				return ret.empty() ? nullptr : ret.top();
//			}
//
//
//
//		std::unordered_map<uint8_t, int> countFrequency(std::vector<std::string>& files) {//读取数据
//				std::unordered_map<uint8_t, int> freqMap;
//				for (const auto& file : files) {
//					std::ifstream inFile(file, std::ios::binary);
//					char ch;
//					while (inFile.get(ch)) {
//						freqMap[ch]++;
//					}
//					inFile.close();
//				}
//				return freqMap;
//			}
//
//
//	void getcodes(Node* root, std::string code, std::unordered_map<uint8_t, std::string>& codes) {
//		if (!root) return;
//		if (!root->left && !root->right) {
//			codes[root->data] = code.empty() ? "0" : code;
//		}
//		getcodes(root->left, code + "0", codes);
//		getcodes(root->right, code + "1", codes);
//	}
//
//
//	void compress(std::string inpath,std::string outpath) {//单文件压缩
//		//单文件：
//		auto freq = countfreq(inpath);//读入文件编码
//		if (freq.empty()) { std::cout << "文件为空" << std::endl; return; }
//		auto root = buildTree(freq);//创建哈夫曼树完成
//		std::unordered_map<uint8_t, std::string>codes;
//		getcodes(root, "", codes);//构建编码
//
//		std::ofstream out(outpath, std::ios::binary);
//		int code_size = codes.size();
//		out.write((char*)&code_size, sizeof(code_size));
//
//		for (const auto& p : codes) {
//			char c = p.first;
//			const std::string& code = p.second;
//			int len = code.size();
//
//			out.write((char*)&c, 1);
//			out.write((char*)&len, sizeof(len));
//
//			std::bitset<8> bits;
//			for (int i = 0; i < len; ++i) {
//				bits[i % 8] = (code[i] == '1');
//				if (i % 8 == 7 || i == len - 1) {
//					out.put((char)bits.to_ulong());
//					bits.reset();
//				}
//			}
//		}
//
//		std::string bits;
//		std::ifstream in(inpath, std::ios::binary);
//		char c;
//		while (in.read((char*)&c, 1)) {
//			bits += codes[c];
//		}
//		in.close();
//
//		int  pad = 8 - (bits.size() % 8);
//		if (pad != 8) bits += std::string(pad, '0');
//		out.write((char*)&pad, sizeof(pad));
//
//		for (size_t i = 0; i < bits.size(); i += 8) {
//			std::bitset<8> b(bits.substr(i, 8));
//			out.put((char)b.to_ulong());
//		}
//		out.close();
//		std::cout << outpath;
//		//多文件：
//
//	}
//
//	void decom(std::string inpath, std::string outpath) {//单文件解压
//		std::ifstream in(inpath, std::ios::binary);
//		if (!in) {
//			std::cerr << "打开失败" << std::endl; exit(1);
//		}
//
//		int codesize;
//		in.read((char*)&codesize, sizeof(codesize));
//		std::unordered_map<std::string, char>codemap;
//
//		for (int i = 0; i < codesize; ++i) {
//			char c;
//			int len;
//			in.read((char*)&c, 1);
//			in.read((char*)&len, sizeof(len));
//
//			std::string code;
//			int bytes = (len + 7) / 8;
//			for (int j = 0; j < bytes; ++j) {
//				char re;
//				in.read((char*)&re, 1);
//				std::bitset<8>b(re);
//				for (int k = 0; k < 8 && code.size() < len; ++k) {
//					code += b[k] ? "1" : "0";
//				}
//			}
//			codemap[code] = c;
//		}
//		int pad;
//		in.read((char*)&pad, sizeof(pad));
//
//		std::string bits;
//		char re;
//		while (in.read((char*)&re, 1)) bits += std::bitset<8>(re).to_string();
//		if (pad != 8) bits = bits.substr(0, bits.size() - pad);
//
//		std::ofstream out(outpath, std::ios::binary);
//		std::string current;
//		for (char bit : bits) {
//			current += bit;
//			if (codemap.count(current)) {
//				out.put(codemap[current]);
//				current.clear();
//			}
//		}
//		out.close();
//		in.close();
//
//		std::cout << "解压结束" << outpath;
//	}
//
//};
//
//
//
//
//
//int main() {
//	
//
//}
