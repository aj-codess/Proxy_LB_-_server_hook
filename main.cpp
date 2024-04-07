#include <iostream>
#include <string>

#include <boost/asio.hpp>

using namespace std;

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

    std::string request="GET / HTTP/1.1\r\nHost: www.google.com\r\n\r\n";
    socket.write_some(boost::asio::buffer(request.data(),request.size()),error_pool);

    socket.wait(socket.wait_read);

    size_t bytes=socket.available();

    if(bytes>0){
        std::vector<char> vBuffer(bytes);
        socket.read_some(boost::asio::buffer(vBuffer.data(),vBuffer.size()),error_pool);

        for(auto c:vBuffer){
            cout<<c;
        };
    }

};


    return 0;
}