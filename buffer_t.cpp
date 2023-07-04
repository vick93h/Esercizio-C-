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
        bufferNotFull.wait(lock,[&buffer]{return buffer->messages.size() < (buffer)->maxSize;});
        (buffer)->messages.push(*msg);
        bufferNotEmpty.notify_all();  // Notifica i consumatori che il buffer non è vuoto
        lock.unlock();
        //msg->msg_destroy(msg);
    }
    catch(const std::exception& e){
        std::cerr << "An exception occurred: " << e.what() << std::endl;

    }
}
msg_t*  buffer_t::get_bloccante(buffer_t* buffer){
    try {
        std::unique_lock<std::mutex> lock(mtx);
        bufferNotEmpty.wait(lock, [&buffer] { return !buffer->messages.empty(); });  // Attende finché il buffer non è vuoto
        msg_t *message=new msg_t();
        *message = (buffer)->messages.front();
        (buffer)->messages.pop();
        bufferNotFull.notify_all();
        lock.unlock();
        //message.msg_destroy(&message);
        return message;
    }
    catch(const std::exception& e){
        std::cerr << "An exception occurred: " << e.what() << std::endl;
        return nullptr;
    }
}

