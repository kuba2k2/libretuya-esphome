#pragma once

#undef O_NONBLOCK
#define O_NONBLOCK 1
#define LWIP_COMPAT_SOCKETS 0
#define IP6ADDR_STRLEN_MAX    46
#define INET6_ADDRSTRLEN IP6ADDR_STRLEN_MAX

#include <lwip/sockets.h>

int accept(int fd_, struct sockaddr *addr, socklen_t *addrlen);
int bind(int fd_, const struct sockaddr *addr, socklen_t addrlen);
int close(int fd_);
int shutdown(int fd_, int how);
int getpeername(int fd_, struct sockaddr *addr, socklen_t *addrlen);
int getsockname(int fd_, struct sockaddr *addr, socklen_t *addrlen);
int getsockopt(int fd_, int level, int optname, void *optval, socklen_t *optlen);
int setsockopt(int fd_, int level, int optname, const void *optval, socklen_t optlen);
int listen(int fd_, int backlog);
ssize_t read(int fd_, void *buf, size_t len);
ssize_t readv(int fd_, const struct iovec *iov, int iovcnt);
ssize_t write(int fd_, const void *buf, size_t len);
ssize_t send(int fd_, void *buf, size_t len, int flags);
ssize_t writev(int fd_, const struct iovec *iov, int iovcnt);
int fcntl(int s, int cmd, int val);
int socket(int domain, int type, int protocol) ;
const char * inet_ntop(int af, const void *src, char *dst, socklen_t size);


#if LWIP_IPV6 == 0
/*
    beken lwip port doesn't define this struct if LWIP_IPV6 is not defined, but bsd_sockets_impl.cpp uses it regardless
*/
struct sockaddr_in6 {
  u8_t            sin6_len;      /* length of this structure    */
  sa_family_t     sin6_family;   /* AF_INET6                    */
  in_port_t       sin6_port;     /* Transport layer port #      */
  u32_t           sin6_flowinfo; /* IPv6 flow information       */
  struct in6_addr sin6_addr;     /* IPv6 address                */
  u32_t           sin6_scope_id; /* Set of interfaces for scope */
};
#endif /* LWIP_IPV6 */

