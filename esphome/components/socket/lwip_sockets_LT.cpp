#include "lwip_sockets_LT.h"

int accept(int fd_, struct sockaddr *addr, socklen_t *addrlen) { return lwip_accept(fd_, addr, addrlen); }
int bind(int fd_, const struct sockaddr *addr, socklen_t addrlen) { return lwip_bind(fd_, addr, addrlen); }
int close(int fd_) { return lwip_close(fd_); }
int shutdown(int fd_, int how) { return lwip_shutdown(fd_, how); }
int getpeername(int fd_, struct sockaddr *addr, socklen_t *addrlen) { return lwip_getpeername(fd_, addr, addrlen); }
int getsockname(int fd_, struct sockaddr *addr, socklen_t *addrlen) { return lwip_getsockname(fd_, addr, addrlen); }
int getsockopt(int fd_, int level, int optname, void *optval, socklen_t *optlen) { return lwip_getsockopt(fd_, level, optname, optval, optlen); }
int setsockopt(int fd_, int level, int optname, const void *optval, socklen_t optlen) { return lwip_setsockopt(fd_, level, optname, optval, optlen); }
int listen(int fd_, int backlog) { return lwip_listen(fd_, backlog); }
ssize_t read(int fd_, void *buf, size_t len) { return lwip_read(fd_, buf, len); }
ssize_t readv(int fd_, const struct iovec *iov, int iovcnt) { return lwip_readv(fd_, iov, iovcnt);  }
ssize_t write(int fd_, const void *buf, size_t len) { return lwip_write(fd_, buf, len); }
ssize_t send(int fd_, void *buf, size_t len, int flags) { return lwip_send(fd_, buf, len, flags); }
ssize_t writev(int fd_, const struct iovec *iov, int iovcnt) { return lwip_writev(fd_, iov, iovcnt); }
int fcntl(int s, int cmd, int val) { return lwip_fcntl(s, cmd, val); };
int socket(int domain, int type, int protocol)  { return lwip_socket(domain, type, protocol); }
const char * inet_ntop(int af, const void *src, char *dst, socklen_t size) { return lwip_inet_ntop(af, src, dst, size); }
