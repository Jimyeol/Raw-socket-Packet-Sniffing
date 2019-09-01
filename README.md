RAW-SOCKET-PACKET-SNIIFFING
===
### Date: 2015-12~
#### university programming assignments.
-------------
네트워크상에서 떠돌아다니는 패킷을 Sniffing하여  각 계층에 대한 
헤더 정보를 분석하는  프로그램을 Raw Socket을 이용하여 구현

### 설계 환경

- WinPcap(Window Packet Capture)  
          - 네트워크 트래픽 포착용 API 구성 (패킷 포착 가능)
- Visual Studio 2010
- MFC/C++
-------------
### 구현내용
Ehternet 
- Destination MAC Address, source MAC Address

IP
- IP version, IP length, Destination IP Address, Source IP Address, Identification, Flags, TTL

TCP
- Destination portNo, source portNo, Checksum, Window Size, Header length, Urgent pointer, Flags

HTTP
- Response Message (Version), Request Message

UDP
- Destination portNo, source portNo, Checksum, Length

DNS
- Transaction ID, Flags, Questions, Answer RRs, Authority RRs, Additional RRs



