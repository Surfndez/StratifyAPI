/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md for rights.

#if defined __link
#include <sys/stat.h>
#endif

#include "fs/Stat.hpp"
#include "sys/Printer.hpp"

using namespace fs;


sys::Printer& operator << (sys::Printer& printer, const fs::Stat & a){
	var::String type;
	if( a.is_directory() ){ type = "directory"; }
	if( a.is_file() ){ type = "file"; }
	if( a.is_device() ){ type = "device"; }
	if( a.is_block_device() ){ type = "block device"; }
	if( a.is_character_device() ){ type = "character device"; }
	if( a.is_socket() ){ type = "socket"; }
	printer.key("type", type);
	if( a.is_file() ){
		printer.key("size", "%ld", a.size());
	}
	printer.key("mode", "0%o", a.permissions().permissions() & 0777);

	return printer;
}

#if defined __link
Stat::Stat(bool is_local) {
	memset(&m_stat, 0, sizeof(m_stat));
	m_is_local = is_local;
}
#else

Stat::Stat() {
	memset(&m_stat, 0, sizeof(m_stat));
}
#endif


bool Stat::is_directory() const {
#if defined __link
	if( m_is_local ){
		return (m_stat.st_mode & S_IFMT) == S_IFDIR;
	}
#endif
	return (m_stat.st_mode & Stat::mode_format) == Stat::mode_directory;
}

bool Stat::is_file() const {
#if defined __link
	if( m_is_local ){
		return (m_stat.st_mode & S_IFMT) == S_IFREG;
	}
#endif
	return (m_stat.st_mode & Stat::mode_format) == Stat::mode_regular;
}

bool Stat::is_device() const {
	return is_block_device() || is_character_device();

}

bool Stat::is_block_device() const {
#if defined __link
	if( m_is_local ){
		return (m_stat.st_mode & S_IFMT) == S_IFBLK;
	}
#endif
	return (m_stat.st_mode & (Stat::mode_format)) == Stat::mode_block;
}

bool Stat::is_character_device() const {
#if defined __link
	if( m_is_local ){
		return (m_stat.st_mode & S_IFMT) == S_IFCHR;
	}
#endif
	return (m_stat.st_mode & (Stat::mode_format)) == Stat::mode_character;
}

bool Stat::is_socket() const {
#if defined __link
	if( m_is_local ){
#if !defined __win32
		return (m_stat.st_mode & S_IFMT) == S_IFSOCK;
#else
		return false;
#endif
	}
#endif
	return (m_stat.st_mode & Stat::mode_format) == Stat::mode_file_socket;
}


u32 Stat::size() const {
	return m_stat.st_size;
}

bool Stat::is_executable() const {
	return false;
}

const var::String Stat::suffix(
		const var::String & path
		){
	size_t pos = path.rfind('.');

	if( pos == var::String::npos ){
		return var::String();
	}

	return path.create_sub_string(
				var::String::Position(pos+1)
				);
}

const var::String Stat::name(
		const var::String & path
		){
	size_t pos = path.rfind('/');

	if( pos == var::String::npos ){
		return path;
	}

	return path.create_sub_string(
				var::String::Position(pos+1)
				);
}

const var::String Stat::parent_directory(
		const var::String & path
		){
	size_t pos = path.rfind('/');

	if( pos == var::String::npos ){
		return var::String();
	}

	return path.create_sub_string(
				var::String::Position(0),
				var::String::Length(pos)
				);
}

const var::String Stat::base_name(
		const var::String & path
		){
	var::String result = name(path);
	size_t pos = result.rfind('.');
	if( pos == var::String::npos ){
		return result;
	}

	return result.create_sub_string(
				var::String::Position(0),
				var::String::Length(pos)
				);
}

const var::String FileInfo::no_suffix(const var::String & path){
	size_t pos = path.rfind('.');

	if( pos == var::String::npos ){
		return var::String();
	}

	return path.create_sub_string(
				var::String::Position(0),
				var::String::Length(pos)
				);
}

bool FileInfo::is_hidden(const var::String & path){
	if( name(path).find(".") == 0 ){
		return true;
	}

	var::String parent = parent_directory(path);
	if( parent != path ){
		return is_hidden( parent_directory(path) );
	}

	return false;

}



