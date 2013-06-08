#include "nids.h"
#include <stdio.h>
#include <stdlib.h>

int g_counter = 0 ;

struct udp_header {
	unsigned short udp_source_port;
	unsigned short udp_destination_port;
	unsigned short udp_length;
	unsigned short udp_checksum;
};

struct icmp_header {
	unsigned int icmp_type;
	unsigned int icmp_code;
	unsigned char icmp_checksum;
	unsigned char icmp_id;
	unsigned char icmp_sequence;
};

struct ip_header {
#if defined(WORDS_BIGENDIAN)
	unsigned char ip_version: 4, /* version */
	ip_header_length: 4; /* length of header */
#else
	unsigned char ip_header_length :4, ip_version :4;
#endif
	unsigned char ip_tos; /* service type */
	unsigned short ip_length; /* total length */
	unsigned short ip_id; /* identity */
	unsigned short ip_off; /* flag and offset */
	unsigned char ip_ttl; /* live time */
	unsigned char ip_protocol; /* protocal type */
	unsigned short ip_checksum; /* checksum */
	struct in_addr ip_souce_address; /* source ip address  */
	struct in_addr ip_destination_address; /* destination ip address */
};

struct tcp_header {
	unsigned char tcp_source_port; /* source port */
	unsigned char tcp_destination_port; /* destination port */
	unsigned short tcp_sequence; /* sequence num */
	unsigned short tcp_acknowledgement; /* acknowledgement num */
#ifdef WORDS_BIGENDIAN
	unsigned int tcp_offset: 4, /* data offset */
	tcp_reserved: 4; /* reserved */
#else
	unsigned int tcp_reserved :4, /* reserved */
	tcp_offset :4; /* data offset */
#endif
	unsigned int tcp_flags; /* flag */
	unsigned char tcp_windows; /* window size */
	unsigned char tcp_checksum; /* check sum */
	unsigned char tcp_urgent_pointer; /* urgent pointer */
};
char ascii_string[10000];
char *char_to_ascii(char ch) {
	char *string;
	ascii_string[0] = 0;
	string = ascii_string;
	if (isgraph(ch))
		*string++ = ch;
	else if (ch == ' ')
		*string++ = ch;
	else if (ch == '\n' || ch == '\r')
		*string++ = ch;
	else
		*string++ = '.';
	*string = 0;
	return ascii_string;
}

void icmp_protocol_packet_callback(const u_char *packet_content) {
	struct icmp_header *icmp_protocol;
	icmp_protocol = (struct icmp_header*) (packet_content + 14 + 20);
	printf("----------  ICMP    ----------\n");
	printf("ICMP type :%d\n", icmp_protocol->icmp_type);
	switch (icmp_protocol->icmp_type)
	{
	case 8:
		printf("ICMP echo reply protocal : \n");
		printf("ICMP code : %d\n", icmp_protocol->icmp_code);
		printf("Identity : %d\n", icmp_protocol->icmp_id);
		printf("Seq num : %d\n", icmp_protocol->icmp_sequence);
		break;
	case 0:
		printf("ICMP echo reply protocal \n");
		printf("ICMP code : %d\n", icmp_protocol->icmp_code);
		printf("Identity : %d\n", icmp_protocol->icmp_id);
		printf("Seq num : %d\n", icmp_protocol->icmp_sequence);
		break;
	default:
		break;
	}
	printf("ICMP check sum : %d\n", ntohs(icmp_protocol->icmp_checksum)); /* get check sum type */
	return;
}

void tcp_protocol_packet_callback(const u_char *packet_content) {
	struct tcp_header *tcp_protocol;
	u_char flags;
	int header_length;
	u_short source_port;
	u_short destination_port;
	u_short windows;
	u_short urgent_pointer;
	u_int sequence;
	u_int acknowledgement;
	unsigned char checksum;
	tcp_protocol = (struct tcp_header*) (packet_content + 14 + 20);
	source_port = ntohs(tcp_protocol->tcp_source_port);

	destination_port = ntohs(tcp_protocol->tcp_destination_port);

	header_length = tcp_protocol->tcp_offset * 4;

	sequence = ntohl(tcp_protocol->tcp_sequence);

	acknowledgement = ntohl(tcp_protocol->tcp_acknowledgement);

	windows = ntohs(tcp_protocol->tcp_windows);

	urgent_pointer = ntohs(tcp_protocol->tcp_urgent_pointer);

	flags = tcp_protocol->tcp_flags;

	checksum = ntohs(tcp_protocol->tcp_checksum);
	printf("-------  TCP   -------\n");
	printf("source port : %d\n", source_port);
	printf("destination port : %d\n", destination_port);
	switch (destination_port) {
	case 80:
		printf("Upper is HTTP\n");
		break;
	case 21:
		printf("Upper is FTP\n");
		break;
	case 23:
		printf("Upper is TELNET\n");
		break;
	case 25:
		printf("Upper is SMTP\n");
		break;
	case 110:
		printf("Upper is POP3\n");
		break;
	default:
		break;
	}
	printf("seq num : %u\n", sequence);
	printf("ack num : %u\n", acknowledgement);
	printf("header length : %d\n", header_length);
	printf("reserved : %d\n", tcp_protocol->tcp_reserved);
	printf("flag : ");
	if (flags & 0x08)
		printf("PSH ");
	if (flags & 0x10)
		printf("ACK ");
	if (flags & 0x02)
		printf("SYN ");
	if (flags & 0x20)
		printf("URG ");
	if (flags & 0x01)
		printf("FIN ");
	if (flags & 0x04)
		printf("RST ");
	printf("\n");
	printf("window size : %d\n", windows);
	printf("check sum : %d\n", checksum);
	printf("urgent pointer : %d\n", urgent_pointer);
}

void udp_protocol_packet_callback(u_char *packet_content) {
	struct udp_header *udp_protocol;
	u_short source_port;
	u_short destination_port;
	u_short length;
	udp_protocol = (struct udp_header*) (packet_content + 20);
	source_port = ntohs(udp_protocol->udp_source_port);

	destination_port = ntohs(udp_protocol->udp_destination_port);

	length = ntohs(udp_protocol->udp_length);
	printf("----------  UDP Header    ----------\n");
	printf("source port : %d\n", source_port);
	printf("destination port : %d\n", destination_port);
	switch (destination_port) {
	case 138:
		printf("NETBIOS Datagram Service\n");
		break;
	case 137:
		printf("NETBIOS Name Service\n");
		break;
	case 139:
		printf("NETBIOS session service\n");
		break;
	case 53:
		printf("name-domain server \n");
		break;
	default:
		break;
	}
	printf("length : %d\n", length);
	printf("check sum : %d\n", ntohs(udp_protocol->udp_checksum));
}

void ip_protocol_packet_callback(u_char *packet_content) {
	struct ip_header *ip_protocol;
	u_int header_length;
	u_int offset;
	u_char tos;
	unsigned short checksum;
	printf("----------  IP header  ----------\n");

	ip_protocol = (struct ip_header*) (packet_content);
	checksum = ntohs(ip_protocol->ip_checksum);

	header_length = ip_protocol->ip_header_length * 4;

	tos = ip_protocol->ip_tos;
	offset = ntohs(ip_protocol->ip_off);
	printf("IP version : %d\n", ip_protocol->ip_version);
	printf("header length : %d\n", header_length);
	printf("TOS:%d\n", tos);
	printf("total length : %d\n", ntohs(ip_protocol->ip_length));
	printf("identity : %d\n", ntohs(ip_protocol->ip_id));
	printf("offset : %d\n", (offset & 0x1fff) * 8);
	printf("live time : %d\n", ip_protocol->ip_ttl);
	printf("protocal : %d\n", ip_protocol->ip_protocol);
	switch (ip_protocol->ip_protocol) {
	case 6:
		printf("Upper is TCP\n");
		break;
	case 17:
		printf("Uppser is UDP\n");
		break;
	case 1:
		printf("Upper is ICMP\n");
		break;
	default:
		break;
	}
	printf("check sum : %d\n", checksum);
	printf("source ip : %s\n", inet_ntoa(ip_protocol->ip_souce_address));
	printf("destination ip : %s\n",
			inet_ntoa(ip_protocol->ip_destination_address));
	switch (ip_protocol->ip_protocol) {
	case 17:
		udp_protocol_packet_callback(packet_content);
		break;

	case 6:
		tcp_protocol_packet_callback(packet_content);
		break;

	case 1:
		icmp_protocol_packet_callback(packet_content);
		break;

	default:
		break;
	}

}

void ip_callback(struct ip *a_packet, int len) {
	ip_protocol_packet_callback(a_packet);

}

void main() {
	if (!nids_init()) {
		printf("error occurs : %s\n", nids_errbuf);
		exit(1);
	}
	nids_register_ip_frag(ip_callback);

	nids_run();
}
