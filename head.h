# SimulationFatBut
class Interface
{
Bool REQ,ACK,DATA,CLK,CHOKE;
//Pin Definition
Bit Receive_Register[sizeof(packet)];
// Register Definition
Bit Send_Register[sizeof(packet)];
Bit Receive_Buffer[sizeof(packet),n];
//Buffer Definition
Bit Send_Buffer[sizeof(packet),n];
Bool Busy_Bit, Recieve_Bit, Transfer_Bit;
// Status Bits
Interface Routing_Algorithm(packet);
// Routing Algorithm
void Control_Logic();
// Control Logic
void Buffer_Operations();
// Circular Buffer Operations
}

struct packet
{
char source_address[];
char dest_address[];
char data[]
int start_timer;
int end_timer;
}
~                                                                                                                                                      
~                                                                                                                                                      
~                                                                                                                                                      
~                                                                                                                                                      
~                                                                                                                                                      
~                                               
