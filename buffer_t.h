//
// Created by vitto on 02/07/2023.
//

#ifndef HOMEWORK_1_BUFFER_T_H
#define HOMEWORK_1_BUFFER_T_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include "msg_t.h"

#define BUFFER_ERROR (msg_t *) nullptr
class buffer_t{
public:
    buffer_t* buffer_init(unsigned int maxsize);
    void buffer_destroy(buffer_t* buffer);
    msg_t* put_bloccante(buffer_t* buffer, msg_t *msg);
    msg_t* get_bloccante(buffer_t* buffer);
    msg_t* put_non_bloccante(buffer_t* buffer, msg_t* msg);
    msg_t* get_non_bloccante(buffer_t* buffer);

private:
    unsigned int maxSize;
    std::queue<msg_t> messages;   //coda di messaggi condivisa
    std::mutex mtx;              //Mutex per garantire l'accesso esclusivo alla coda
    std::condition_variable bufferNotEmpty;
    std::condition_variable bufferNotFull;

};


#endif //HOMEWORK_1_BUFFER_T_H
