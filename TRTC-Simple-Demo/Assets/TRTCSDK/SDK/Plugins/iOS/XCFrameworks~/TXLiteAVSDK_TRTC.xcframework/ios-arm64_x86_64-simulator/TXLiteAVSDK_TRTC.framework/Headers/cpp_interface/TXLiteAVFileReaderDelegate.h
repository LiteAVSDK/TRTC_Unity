
// Copyright (c) 2023 Tencent. All rights reserved.

#ifndef __TXLITEAVFILEREADERDELEGATE_H__
#define __TXLITEAVFILEREADERDELEGATE_H__

#include <cstdint>

namespace liteav {

class TXLiteAVFileReaderDelegate {
 public:
  virtual ~TXLiteAVFileReaderDelegate() {}

  /**
   * 打开文件
   *
   * @param path 文件路径。
   * @return 成功返回文件句柄，失败返回 -1。
   */
  virtual int64_t open(const char* path) = 0;

  /**
   * 关闭文件
   *
   * @param file 文件句柄，由 open 方法返回。
   */
  virtual void close(int64_t file) = 0;

  /**
   * 读取文件
   *
   * @param buffer 存储读取数据的内存地址。
   * @param size 要读取的数据大小。
   * @param file 文件句柄。
   * @return 实际读取的大小，已读到文件末尾时返回 0, 失败时返回 -1。
   */
  virtual int read(unsigned char* buffer, int size, int64_t file) = 0;

  /**
   * 定位文件位置（可参照 fseek 函数实现）
   *
   * @param offset 偏移量（正数或负数），表示相对于起始位置移动文件指针的字节数。
   * @param whence 位移的起始位置，0:文件开头，1:当前文件指针的位置，2:文件末尾。
   * @param file 文件句柄。
   * @return 成功返回 0，失败返回 -1。
   */
  virtual int64_t seek(int64_t offset, int whence, int64_t file) = 0;

  /**
   * 获取文件大小
   *
   * @param file 文件句柄。
   * @return 文件大小
   */
  virtual int64_t getSize(int64_t file) = 0;
};

}  // namespace liteav

#endif  // __TXLITEAVFILEREADERDELEGATE_H__
