#ifndef ASSETS_H
#define ASSETS_H

#include <map>
#include <string>

// TODO: Maybe inherit values from Lexer, especially
// once res_header becomes more complicated (but what
// about the method(s) of Lexer?)?
class Assets {
public:
	/*
	Assets ()
	{
		// Possibly some kind of error checking,
		// initialising files, storing them in the
		// object (which can be closed in the deconstructor)?
	}
	*/

	void req_store(char* buffer);
	std::string res_route(std::string target);

private:
	int req_num = 0;

	// https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status#successful_responses
	int error_code = 200;
	std::map<int, std::string> psbl_error_msgs = {
		// "Informational responses"
		{ 100, "100 Continue" },

		// "Sucessful responses"
		{ 200, "200 OK" },

		// "Redirection messages"
		{ 300, "300 Multiple Choices" },
		{ 308, "308 Permanent Redirect" },

		// "Client error responses"
		{ 400, "400 Bad Request" },
		{ 404, "404 Not Found" },
		{ 405, "405 Method Not Allowed" },
		{ 408, "408 Request Timeout" },
		{ 411, "411 Length Required" },
		{ 413, "413 Content Too Large" },
		{ 414, "414 URI Too Long" },
		{ 415, "415 Unsupported Media Type" },
		{ 416, "416 Range Not Satisfiable" },
		{ 417, "417 Expectation Failed" },
		{ 418, "418 I'm a teapot" },
		{ 421, "421 Misdirected Request" },
		{ 426, "426 Upgrade Required" },
		{ 428, "428 Precondition Required" },
		{ 429, "429 Too Many Requests" },
		{ 431, "431 Request Header Fields Too Large" },
		{ 451, "451 Unavailable For Legal Reasons" },

		// "Server error responses"
		{ 500, "500 Internal Server Error" },
		{ 501, "501 Not Implemented" },
		{ 502, "502 Bad Gateway" },
		{ 503, "503 Service Unavailable" },
		{ 504, "504 Gateway Timeout" },
		{ 505, "505 HTTP Version Not Supported" },
	};

	std::string content;
	std::string payload;
	std::string content_type = "text/html";

	std::string res_content(std::string target);
	std::string res_header();
};

#endif
