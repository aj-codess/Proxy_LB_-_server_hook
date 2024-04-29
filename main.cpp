#include <iostream>
#include <string>

#include <boost/asio.hpp>

using namespace std;


std::vector<char> virtual_buffer(20*1024);

void data_2_grab(boost::asio::ip::tcp::socket& socket){

    socket.async_read_some(boost::asio::buffer(virtual_buffer.data(),virtual_buffer.size()),[&](boost::system::error_code error_pool,std::size_t length){
        if(!error_pool){
            for(int i=0;i<length;i++){
                cout<<virtual_buffer[i]<<endl;
            };
            data_2_grab(socket);
        };
    });

};



int main(){
    
boost::system::error_code error_pool;
boost::asio::io_context context;
boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::make_address("172.217.167.78",error_pool),80);
boost::asio::ip::tcp::socket socket(context);

socket.connect(endpoint,error_pool);

if(!error_pool){
    cout<<"connected...."<<endl;
} else{
    cout<<"there was an error connecting to the address- \n "<<error_pool.message()<<endl;  
};


if(socket.is_open()){

    data_2_grab(socket);

    std::string request="GET / HTTP/1.1\r\nHost: www.google.com\r\n\r\n";
    socket.write_some(boost::asio::buffer(request.data(),request.size()),error_pool);

};

    return 0;
}