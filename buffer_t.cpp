#include <iostream>
#include "buffer_t.h"

//
// Created by vitto on 02/07/2023.
//
buffer_t* buffer_t::buffer_init(unsigned int maxsize){
         (this)->maxSize=maxsize;
         return this;
}
void buffer_t::put_bloccante(buffer_t *buffer, msg_t *msg) {
    try {
        std::unique_lock<std::mutex> lock(mtx);
        bufferNotFull.wait(lock,[&buffer](){return buffer->messages.size() < (buffer)->maxSize;});
        (buffer)->messages.push(*msg);
        bufferNotEmpty.notify_one();  // Notifica i consumatori che il buffer non è vuoto
    }
    catch(const std::system_error& e){
        std::cout << "Caught a system_error\n";
        if (e.code() == std::errc::invalid_argument)
            std::cout << "The error condition is 'std::errc::invalid_argument'\n";
        std::cout << "The error description is '" << e.what() << "'\n";
    }


}
msg_t*  buffer_t::get_bloccante(buffer_t* buffer){
    try {
        std::unique_lock<std::mutex> lock(mtx);
        bufferNotEmpty.wait(lock, [&buffer]() { return !buffer->messages.empty(); });  // Attende finché il buffer non è vuoto
        msg_t* message = new msg_t ((buffer)->messages.front());
        (buffer)->messages.pop();
        bufferNotFull.notify_one();
        return message;
    }
    catch(const std::system_error& e){
        std::cout << "Caught a system_error\n";
        if (e.code() == std::errc::invalid_argument)
            std::cout << "The error condition is 'std::errc::invalid_argument'\n";
        std::cout << "The error description is '" << e.what() << "'\n";
        return nullptr;
    }
}

