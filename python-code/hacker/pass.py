# https://tools.ietf.org/pdf/rfc7230.pdf

# https://tools.ietf.org/pdf/rfc6265.pdf
# This document defines the HTTP Cookie and Set-Cookie header fields.
# These header fields can be used by HTTP servers to store state
# (called cookies) at HTTP user agents, letting the servers maintain a
# stateful session over the mostly stateless HTTP protocol. 


# OWS (optional whitespace), RWS (required whitespace), and BWS ("bad" whitespace).
# HTAB (horizontal tab)

import socket

CRLF='\r\n'
# HTTP-message   = start-line
#                  *( header-field CRLF )
#                  CRLF
#                  [ message-body ]

# request-line   = method SP request-target SP HTTP-version CRLF
# header-field   = field-name ":" OWS field-value OWS
# message-body = *OCTET


# Recipients typically parse the request-line into its component parts
# by splitting on whitespace (see Section 3.5), since no whitespace is
# allowed in the three components.
request_line = "GET / HTTP/1.1" + CRLF

# Header fields
# 1. Each header field consists of a case-insensitive field name followed
#    by a colon (":"), optional leading whitespace, the field value, and
#    optional trailing whitespace.
# 2. No whitespace is allowed between the header field-name and colon. 
# 3. A field value might be preceded and/or followed by optional
#    whitespace (OWS); a single SP preceding the field-value is preferred
#    for consistent readability by humans.

# 4, A string of text is parsed as a single value if it is quoted using
#    double-quote marks.
host = "Host: www.hackthissite.org" + CRLF
headers = host

message=request_line + headers+ CRLF

def mysend(message):
    print message
    s=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect(("www.hackthissite.org", 80))
    s.sendall(message)
    buf = ''
    bytes = s.recv(2048)
    while bytes:
        buf += bytes
        # print bytes
        bytes = s.recv(2048)
    return buf

def writeFile(filename, str):
    f = open(filename, 'w')
    f.write(str)
    f.close()

def getCookie(buf):
    setCookie = buf.index("Set-Cookie:")
    end = buf[setCookie:].index(';') + setCookie
    line_end = buf[setCookie:].index(CRLF) + setCookie
    print buf[setCookie:line_end]
    print buf[setCookie:end]
    cookie = buf[setCookie:end].split(':')[1].strip()
    print cookie
    return cookie


buf = mysend(message)
writeFile('1.html', buf)
cookie = getCookie(buf)

# A sender MUST NOT send a Content-Length header field in any message
# that contains a Transfer-Encoding header field.

# A user agent SHOULD send a Content-Length in a request message when
# no Transfer-Encoding is sent and the request method defines a meaning
# for an enclosed payload body.  For example, a Content-Length header
# field is normally sent in a POST request even when the value is 0


body = "username=&password=f585e4f3aa39&btn_submit=Login"
body = body.replace('_', '%5f')
body_len = len(body)

# the second request
clientCookie = "Cookie: " + cookie + CRLF
referer = "Referer: http://www.hackthissite.org/" + CRLF
# transfer_encoding = "Transfer-Encoding: chunked" + CRLF
content_type = "Content-Type: application/x-www-form-urlencoded" + CRLF
content_length = "Content-Length: " + str(body_len) + CRLF
headers += clientCookie + content_type + content_length + referer

request_line = "POST /user/login HTTP/1.1" + CRLF
message=request_line + headers+ CRLF + body

print message
writeFile('2.html', mysend(message))
# message-body = *OCTET
# The presence of a message body in a request is signaled by a
# Content-Length or Transfer-Encoding header field. 
