/*! \file */ //Copyright 2011-2018 Tyler Gilbert; All Rights Reserved

#ifndef HTTP_HPP
#define HTTP_HPP

#include "Socket.hpp"
#include "../api/InetObject.hpp"
#include "../var/String.hpp"
#include "../sys/ProgressCallback.hpp"

namespace inet {

class Http : public api::InetWorkObject {
public:
	Http(Socket & socket);


protected:
	Socket & socket(){ return m_socket; }

private:
	//server name
	//port

	//socket to use
	Socket & m_socket;

};


class HttpClient : public Http {
public:
	HttpClient(Socket & socket);

	/*! \details Keeps the connection alive between requests.
	 *
	 * @param value If true, the connection is kept alive between requests
	 *
	 *
	 */
	void set_keep_alive(bool value = true){ m_is_keep_alive = value; }

	bool is_keep_alive() const { return m_is_keep_alive; }

	int head(const var::ConstString & url);
	int get(const var::ConstString & url, const sys::File & response, const sys::ProgressCallback * progress_callback = 0);

	int post(const var::ConstString & url, const var::ConstString & request, const sys::File & response, const sys::ProgressCallback * progress_callback = 0);
	int post(const var::ConstString & url, const sys::File & request, const sys::File & response, const sys::ProgressCallback * progress_callback = 0);

	int put(const var::ConstString & url, const var::ConstString & request, const sys::File & response, const sys::ProgressCallback * progress_callback = 0);
	int put(const var::ConstString & url, const sys::File & request, const sys::File & response, const sys::ProgressCallback * progress_callback = 0);

	int patch(const var::ConstString & url, const var::ConstString & request, const sys::File & response, const sys::ProgressCallback * progress_callback = 0);
	int patch(const var::ConstString & url, const sys::File & request, const sys::File & response, const sys::ProgressCallback * progress_callback = 0);

	//http delete
	int remove(const var::ConstString & url, const var::String & data);
	int options(const var::ConstString & url);
	int trace(const var::ConstString & url);
	int connect(const var::ConstString & url);


	/*! \details Returns a reference to the header that is returned
	  * by the request.
	  *
	  */
	const var::String & header() const { return m_header; }
	const var::String & header_response() const { return m_header_response; }

	/*! \details Returns the status code of the last request.
	 *
	 * The status code will be 200 for a successful request.
	 *
	 */
	int status_code() const { return m_status_code; }

	u32 transfer_size() const {
		return m_transfer_size;
	}

	void set_transfer_size(u32 value){
		m_transfer_size = value;
	}

	void set_chunked_transfer_encoding_enabled(bool value = true){
		m_is_chunked_transfer_encoding = value;
	}

	int close_connection();

	var::Vector<var::String> & header_request_fields(){ return m_header_request_fields; }
	const var::Vector<var::String> & header_request_fields() const { return m_header_request_fields; }

	var::Vector<var::String> & header_response_fields(){ return m_header_response_fields; }
	const var::Vector<var::String> & header_response_fields() const { return m_header_response_fields; }

private:


	int connect_to_server(const var::ConstString & domain_name, u16 port);

	int query(const var::ConstString & command,
				 const var::ConstString & url,
				 const sys::File * send_file,
				 const sys::File * get_file,
				 const sys::ProgressCallback * progress_callback);


	int send_string(const var::ConstString & str);

	int build_header(const var::ConstString & method, const var::ConstString & host, const var::ConstString & path, u32 length);

	int send_header(const var::ConstString & method,
						 const var::ConstString & host,
						 const var::ConstString & path,
						 const sys::File * file,
						 const sys::ProgressCallback * progress_callback);

	int listen_for_header();
	int listen_for_data(const sys::File & file, const sys::ProgressCallback * progress_callback);

	SocketAddress m_address;

	var::String m_transfer_encoding;
	var::Vector<var::String> m_header_request_fields;
	var::Vector<var::String> m_header_response_fields;
	var::String m_header;
	var::String m_header_response;
	int m_status_code;

	int m_content_length;
	bool m_is_keep_alive;

	bool m_is_chunked_transfer_encoding;
	u32 m_transfer_size;

};

class HttpServer : public Http {
public:
	HttpServer();


private:

	//path to filesystem
	//callback for dynamic content

	//design to be easily used in a thread


};

}

#endif // HTTP_HPP
