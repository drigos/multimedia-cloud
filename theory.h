#ifndef THEORY
#define THEORY

#include <stdio.h>

void address_family_socket() {
   //printf("%5d: \n", );
   puts("\nAddress Family\n");
   printf("%5d: AF_UNSPEC\n", AF_UNSPEC);
   printf("%5d: AF_UNIX\n", AF_UNIX);
   printf("%5d: AF_INET\n", AF_INET);
   printf("%5d: AF_AX25\n", AF_AX25);
   printf("%5d: AF_IPX\n", AF_IPX);
   printf("%5d: AF_APPLETALK\n", AF_APPLETALK);
   printf("%5d: AF_NETROM\n", AF_NETROM);
   printf("%5d: AF_BRIDGE\n", AF_BRIDGE);
   printf("%5d: AF_ATMPVC\n", AF_ATMPVC);
   printf("%5d: AF_X25\n", AF_X25);
   printf("%5d: AF_INET6\n", AF_INET6);
   printf("%5d: AF_ROSE\n", AF_ROSE);
   printf("%5d: AF_DECnet\n", AF_DECnet);
   printf("%5d: AF_NETBEUI\n", AF_NETBEUI);
   printf("%5d: AF_SECURITY\n", AF_SECURITY);
   printf("%5d: AF_KEY\n", AF_KEY);
   printf("%5d: AF_NETLINK\n", AF_NETLINK);
   printf("%5d: AF_ROUTE\n", AF_ROUTE);
   printf("%5d: AF_PACKET\n", AF_PACKET);
   printf("%5d: AF_ASH\n", AF_ASH);
   printf("%5d: AF_ECONET\n", AF_ECONET);
   printf("%5d: AF_ATMSVC\n", AF_ATMSVC);
   printf("%5d: AF_RDS\n", AF_RDS);
   printf("%5d: AF_SNA\n", AF_SNA);
   printf("%5d: AF_IRDA\n", AF_IRDA);
   printf("%5d: AF_PPPOX\n", AF_PPPOX);
   printf("%5d: AF_WANPIPE\n", AF_WANPIPE);
   printf("%5d: AF_LLC\n", AF_LLC);
   printf("%5d: AF_CAN\n", AF_CAN);
   printf("%5d: AF_TIPC\n", AF_TIPC);
   printf("%5d: AF_BLUETOOTH\n", AF_BLUETOOTH);
   printf("%5d: AF_IUCV\n", AF_IUCV);
   printf("%5d: AF_RXRPC\n", AF_RXRPC);
   printf("%5d: AF_ISDN\n", AF_ISDN);
   printf("%5d: AF_PHONET\n", AF_PHONET);
   printf("%5d: AF_IEEE802154\n", AF_IEEE802154);
   printf("%5d: AF_CAIF\n", AF_CAIF);
   printf("%5d: AF_ALG\n", AF_ALG);
   printf("%5d: AF_NFC\n", AF_NFC);
   printf("%5d: AF_MAX\n", AF_MAX);
}

void protocol_family_socket() {
   puts("\nProtocol Family\n");
   printf("%5d: PF_UNSPEC\n", PF_UNSPEC);
   printf("%5d: PF_UNIX\n", PF_UNIX);
   printf("%5d: PF_INET\n", PF_INET);
   printf("%5d: PF_AX25\n", PF_AX25);
   printf("%5d: PF_IPX\n", PF_IPX);
   printf("%5d: PF_APPLETALK\n", PF_APPLETALK);
   printf("%5d: PF_NETROM\n", PF_NETROM);
   printf("%5d: PF_BRIDGE\n", PF_BRIDGE);
   printf("%5d: PF_ATMPVC\n", PF_ATMPVC);
   printf("%5d: PF_X25\n", PF_X25);
   printf("%5d: PF_INET6\n", PF_INET6);
   printf("%5d: PF_ROSE\n", PF_ROSE);
   printf("%5d: PF_DECnet\n", PF_DECnet);
   printf("%5d: PF_NETBEUI\n", PF_NETBEUI);
   printf("%5d: PF_SECURITY\n", PF_SECURITY);
   printf("%5d: PF_KEY\n", PF_KEY);
   printf("%5d: PF_NETLINK\n", PF_NETLINK);
   printf("%5d: PF_ROUTE\n", PF_ROUTE);
   printf("%5d: PF_PACKET\n", PF_PACKET);
   printf("%5d: PF_ASH\n", PF_ASH);
   printf("%5d: PF_ECONET\n", PF_ECONET);
   printf("%5d: PF_ATMSVC\n", PF_ATMSVC);
   printf("%5d: PF_RDS\n", PF_RDS);
   printf("%5d: PF_SNA\n", PF_SNA);
   printf("%5d: PF_IRDA\n", PF_IRDA);
   printf("%5d: PF_PPPOX\n", PF_PPPOX);
   printf("%5d: PF_WANPIPE\n", PF_WANPIPE);
   printf("%5d: PF_LLC\n", PF_LLC);
   printf("%5d: PF_CAN\n", PF_CAN);
   printf("%5d: PF_TIPC\n", PF_TIPC);
   printf("%5d: PF_BLUETOOTH\n", PF_BLUETOOTH);
   printf("%5d: PF_IUCV\n", PF_IUCV);
   printf("%5d: PF_RXRPC\n", PF_RXRPC);
   printf("%5d: PF_ISDN\n", PF_ISDN);
   printf("%5d: PF_PHONET\n", PF_PHONET);
   printf("%5d: PF_IEEE802154\n", PF_IEEE802154);
   printf("%5d: PF_CAIF\n", PF_CAIF);
   printf("%5d: PF_ALG\n", PF_ALG);
   printf("%5d: PF_NFC\n", PF_NFC);
   printf("%5d: PF_MAX\n", PF_MAX);
}

void type_socket() {
   puts("\nType\n");
   printf("%5d: SOCK_STREAM\n", SOCK_STREAM);
   printf("%5d: SOCK_DGRAM\n", SOCK_DGRAM);
   printf("%5d: SOCK_RAW\n", SOCK_RAW);
   printf("%5d: SOCK_RDM\n", SOCK_RDM);
   printf("%5d: SOCK_SEQPACKET\n", SOCK_SEQPACKET);
   printf("%5d: SOCK_PACKET\n", SOCK_PACKET);
}

#endif
