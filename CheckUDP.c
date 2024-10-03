#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include "Global.h"

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32")

// Set the packing to a 1 byte boundary
#include <pshpack1.h>

//
// Define the IPv4 header. Make the version and length field one
// character since we can't declare two 4 bit fields without
// the compiler aligning them on at least a 1 byte boundary.
//
typedef struct ip_hdr
{
    unsigned char  ip_verlen;        // 4-bit IPv4 version
                                     // 4-bit header length (in 32-bit words)
    unsigned char  ip_tos;           // IP type of service
    unsigned short ip_totallength;   // Total length
    unsigned short ip_id;            // Unique identifier
    unsigned short ip_offset;        // Fragment offset field
    unsigned char  ip_ttl;           // Time to live
    unsigned char  ip_protocol;      // Protocol(TCP,UDP etc)
    unsigned short ip_checksum;      // IP checksum
    unsigned int   ip_srcaddr;       // Source address
    unsigned int   ip_destaddr;      // Source address
} IPV4_HDR, *PIPV4_HDR, FAR * LPIPV4_HDR;

//
// Define the UDP header
//
typedef struct udp_hdr
{
    unsigned short src_portno;       // Source port no.
    unsigned short dst_portno;       // Dest. port no.
    unsigned short udp_length;       // Udp packet length
    unsigned short udp_checksum;     // Udp checksum (optional)
} UDP_HDR, *PUDP_HDR;

// Restore the byte boundary back to the previous value
#include <poppack.h>
//

// Function: checksum
//
// Description:
//    This function calculates the 16-bit one's complement sum
//    for the supplied buffer.
//
USHORT checksum(USHORT *buffer, int size)
{
    unsigned long cksum=0;

    while (size > 1)
    {
        cksum += *buffer++;
        size  -= sizeof(USHORT);   
    }
    if (size)
    {
        cksum += *(UCHAR*)buffer;   
    }
    cksum = (cksum >> 16) + (cksum & 0xffff);
    cksum += (cksum >>16);

    return (USHORT)(~cksum);
}

//
// Function: InitIpv4Header
//
// Description:
//    Initialize the IPv4 header with the version, header length,
//    total length, ttl, protocol value, and source and destination
//    addresses.
//
int InitIpv4Header(
    char *buf,
    char *src,
    char *dest,
    int payloadlen
    )
{
    IPV4_HDR    *v4hdr=NULL;

    v4hdr = (IPV4_HDR *)buf;

    v4hdr->ip_verlen      = (4 << 4) | (sizeof(IPV4_HDR) / sizeof(unsigned long));
    v4hdr->ip_tos         = 0;
    v4hdr->ip_totallength = htons(sizeof(IPV4_HDR) + payloadlen);
    v4hdr->ip_id          = 0;
    v4hdr->ip_offset      = 0;
    v4hdr->ip_ttl         = 128;
    v4hdr->ip_protocol    = 0x11;
    v4hdr->ip_checksum    = 0;
    v4hdr->ip_srcaddr     = inet_addr(src);
    v4hdr->ip_destaddr    = inet_addr(dest);

    v4hdr->ip_checksum    = checksum((unsigned short *)v4hdr, sizeof(IPV4_HDR));
    
    return sizeof(IPV4_HDR);
}

//
// Function: ComputeUdpPseudoHeaderChecksumV4
//
// Description:
//    Compute the UDP pseudo header checksum. The UDP checksum is based
//    on the following fields:
//       o source IP address
//       o destination IP address
//       o 8-bit zero field
//       o 8-bit protocol field
//       o 16-bit UDP length
//       o 16-bit source port
//       o 16-bit destination port
//       o 16-bit UDP packet length
//       o 16-bit UDP checksum (zero)
//       o UDP payload (padded to the next 16-bit boundary)
//    This routine copies these fields to a temporary buffer and computes
//    the checksum from that.
//
void ComputeUdpPseudoHeaderChecksumV4(
    void    *iphdr,
    UDP_HDR *udphdr,
    char    *payload,
    int      payloadlen
    )
{
	IPPacket packet;

    IPV4_HDR     *v4hdr=NULL;
    unsigned long zero=0;
    char          buf[1000],
                 *ptr=NULL;
    int           chksumlen=0,
                  i;

    InitializeIPPacket(&packet);

	InitializeUDPPacket(&packet.udpPacket);
	packet.ipSource[0] = 10;packet.ipSource[1] = 7;packet.ipSource[2] = 0;packet.ipSource[3] = 5;
	packet.ipDestination[0] = 10;packet.ipDestination[1] = 7;packet.ipDestination[2] = 0;packet.ipDestination[3] = 6;
	//Set source.
	packet.udpPacket.nSourcePort = 1701;
	packet.udpPacket.nDestinationPort = 1701;

	packet.udpPacket.nLength = payloadlen + 4 * sizeof(short);

	memcpy((_BYTE *)packet.udpPacket.buffer.block,payload,payloadlen);
	packet.udpPacket.buffer.nCount = payloadlen;

	GetUDPPacketChecksum(packet.ipSource,packet.ipDestination,&packet.udpPacket);

    ptr = buf;

    v4hdr = (IPV4_HDR *)iphdr;

    // Include the source and destination IP addresses
    memcpy(ptr, &v4hdr->ip_srcaddr,  sizeof(v4hdr->ip_srcaddr));  
    ptr += sizeof(v4hdr->ip_srcaddr);
    chksumlen += sizeof(v4hdr->ip_srcaddr);

    memcpy(ptr, &v4hdr->ip_destaddr, sizeof(v4hdr->ip_destaddr));
    ptr += sizeof(v4hdr->ip_destaddr);
    chksumlen += sizeof(v4hdr->ip_destaddr);
    
    // Include the 8 bit zero field
    memcpy(ptr, &zero, 1);
    ptr++;
    chksumlen += 1;

    // Protocol
    memcpy(ptr, &v4hdr->ip_protocol, sizeof(v4hdr->ip_protocol));
    ptr += sizeof(v4hdr->ip_protocol);
    chksumlen += sizeof(v4hdr->ip_protocol);

    // UDP length
    memcpy(ptr, &udphdr->udp_length, sizeof(udphdr->udp_length));
    ptr += sizeof(udphdr->udp_length);
    chksumlen += sizeof(udphdr->udp_length);
    
    // UDP source port
    memcpy(ptr, &udphdr->src_portno, sizeof(udphdr->src_portno));
    ptr += sizeof(udphdr->src_portno);
    chksumlen += sizeof(udphdr->src_portno);

    // UDP destination port
    memcpy(ptr, &udphdr->dst_portno, sizeof(udphdr->dst_portno));
    ptr += sizeof(udphdr->dst_portno);
    chksumlen += sizeof(udphdr->dst_portno);

    // UDP length again
    memcpy(ptr, &udphdr->udp_length, sizeof(udphdr->udp_length));
    ptr += sizeof(udphdr->udp_length);
    chksumlen += sizeof(udphdr->udp_length);
   
    // 16-bit UDP checksum, zero
    memcpy(ptr, &zero, sizeof(unsigned short));
    ptr += sizeof(unsigned short);
    chksumlen += sizeof(unsigned short);

    // payload
    memcpy(ptr, payload, payloadlen);
    ptr += payloadlen;
    chksumlen += payloadlen;

    // pad to next 16-bit boundary
    for(i=0 ; i < payloadlen%2 ; i++, ptr++)
    {
        printf("pad one byte\n");
        *ptr = 0;
        ptr++;
        chksumlen++;
    }

    // Compute the checksum and put it in the UDP header
    udphdr->udp_checksum = checksum((USHORT *)buf, chksumlen);

	printf("Check sum = 0x%04x",udphdr->udp_checksum);

    return;
}

//
// Function: InitUdpHeader
//
// Description:
//    Setup the UDP header which is fairly simple. Grab the ports and
//    stick in the total payload length.
//
int InitUdpHeader(
    char *buf,
    int srcprt,
    int dstprt,
    int       payloadlen
    )
{
    UDP_HDR *udphdr=NULL;

    udphdr = (UDP_HDR *)buf;
    udphdr->src_portno = htons(srcprt);
    udphdr->dst_portno = htons(dstprt);
    udphdr->udp_length = htons(sizeof(UDP_HDR) + payloadlen);

    return sizeof(UDP_HDR);
}


//
// Function: sendudp
//
// Description:
//    Send the udp packets with RAW SOCKET
//
int sendudp(char *srcip, char *dstip, int srcprt, int dstprt, char *buf, int bufsize)
{
    WSADATA            wsd;
    SOCKET             s;
    char sendbuf[1000]={0};
    int           iphdrlen,
                  allsize,
                  udphdrlen;
    int     optlevel,
                option,
                optval,
                rc;  
    SOCKADDR_IN    ReceiverAddr;

    ReceiverAddr.sin_family = AF_INET;
    ReceiverAddr.sin_port = htons(dstprt);    
    ReceiverAddr.sin_addr.s_addr = inet_addr(dstip);
    
    allsize = sizeof(IPV4_HDR) + sizeof(UDP_HDR) + bufsize;
    if (WSAStartup(MAKEWORD(2,2), &wsd) != 0)
    {
        printf("WSAStartup() failed: %d\n", GetLastError());
        return -1;
    }

    s = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if (s == INVALID_SOCKET)
    {
        fprintf(stderr, "socket failed: %d\n", WSAGetLastError());
        return -1;
    }

    // Enable the IP header include option
    optval = 1;
    optlevel = IPPROTO_IP;
    option   = IP_HDRINCL;
    rc = setsockopt(s, optlevel, option, (char *)&optval, sizeof(optval));
    if (rc == SOCKET_ERROR)
    {
        fprintf(stderr, "setsockopt: IP_HDRINCL failed: %d\n", WSAGetLastError());
        return -1;
    }

    
    // Initialize the v4 header
    iphdrlen = InitIpv4Header(
            sendbuf,
            srcip,
            dstip,
            bufsize
            );

    // Initialize the UDP header
    udphdrlen = InitUdpHeader(
           &sendbuf[iphdrlen],
            srcprt,
            dstprt,
            bufsize
            );

    // Compute the UDP checksum
    ComputeUdpPseudoHeaderChecksumV4(
            sendbuf,
            (UDP_HDR *)&sendbuf[iphdrlen],
            buf,
            bufsize
            );

    // Copy the payload to the end of the header
    memcpy(&sendbuf[iphdrlen + udphdrlen], buf, bufsize);

    rc = sendto(
                        s,
                        sendbuf,
                        allsize,
                        0,
                        (const struct sockaddr*)&ReceiverAddr,
                        sizeof(ReceiverAddr)
                        );
    if (rc == SOCKET_ERROR)
    {
        printf("sendto() failed: %d\n", WSAGetLastError());
    }
    else
    {
        printf("sent %d bytes\n", rc);
    }
    closesocket(s) ;
    WSACleanup() ;

    return 0;
}

int main(int argc, char **argv)
{
     while(1)
        sendudp("10.7.0.5", "10.7.0.6", 1701, 1701, "test\x00\x55",6);
     getchar();
    return 0;
}