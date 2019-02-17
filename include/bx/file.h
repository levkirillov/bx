/*
 * Copyright 2010-2019 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bx#license-bsd-2-clause
 */

#ifndef BX_FILE_H_HEADER_GUARD
#define BX_FILE_H_HEADER_GUARD

#include "filepath.h"
#include "readerwriter.h"

namespace bx
{
	///
	ReaderI* getStdIn();

	///
	WriterI* getStdOut();

	///
	WriterI* getStdErr();

	///
	WriterI* getNullOut();

	///
	class FileReader : public FileReaderI
	{
	public:
		///
		FileReader();

		///
		virtual ~FileReader();

		///
		virtual bool open(const FilePath& _filePath, Error* _err) override;

		///
		virtual void close() override;

		///
		virtual int64_t seek(int64_t _offset = 0, Whence::Enum _whence = Whence::Current) override;

		///
		virtual int32_t read(void* _data, int32_t _size, Error* _err) override;

	private:
		BX_ALIGN_DECL(16, uint8_t) m_internal[64];
	};

	///
	class FileWriter : public FileWriterI
	{
	public:
		///
		FileWriter();

		///
		virtual ~FileWriter();

		///
		virtual bool open(const FilePath& _filePath, bool _append, Error* _err) override;

		///
		virtual void close() override;

		///
		virtual int64_t seek(int64_t _offset = 0, Whence::Enum _whence = Whence::Current) override;

		///
		virtual int32_t write(const void* _data, int32_t _size, Error* _err) override;

	private:
		BX_ALIGN_DECL(16, uint8_t) m_internal[64];
	};

	struct FileType
	{
		enum Enum
		{
			File,
			Dir,

			Count
		};
	};

	///
	struct FileInfo
	{
		FilePath filePath;
		uint64_t size;
		FileType::Enum type;
	};

	///
	class DirectoryReader : public ReaderOpenI, public CloserI, public ReaderI
	{
	public:
		///
		DirectoryReader();

		///
		virtual ~DirectoryReader();

		///
		virtual bool open(const FilePath& _filePath, Error* _err) override;

		///
		virtual void close() override;

		///
		virtual int32_t read(void* _data, int32_t _size, Error* _err) override;

	private:
		BX_ALIGN_DECL(16, uint8_t) m_internal[sizeof(FilePath)+sizeof(FileInfo)+16];
	};

	///
	bool stat(FileInfo& _outFileInfo, const FilePath& _filePath);

} // namespace bx

#endif // BX_FILE_H_HEADER_GUARD
