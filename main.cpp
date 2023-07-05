#include <iostream>
#include <thread>
#include "buffer_t.h"

void producer(buffer_t *buffer, int producer_id,int numMessage);
void consumer(buffer_t *buffer, int consumer_id,int numMessage);
int main() {
    try {
        buffer_t *buffer = new buffer_t();
        buffer->buffer_init(10);
        std::thread producers(producer, buffer, 1,5);
        std::thread consumers(consumer, buffer, 1,5);
        producers.join();
        consumers.join();
        return 0;
    }
    catch(const std::system_error& e){
        std::cout << "Caught a system_error\n";
        if (e.code() == std::errc::invalid_argument)
            std::cout << "The error condition is 'std::errc::invalid_argument'\n";
        std::cout << "The error description is '" << e.what() << "'\n";
        return -1;
    }
}
void producer(buffer_t * buffer, int producer_id,int numMessage) {
    try {
        for (int i = 0; i < numMessage; i++) {
            msg_t* message=new msg_t();
            message->msg_init(new int(i));
            //message->setContent(new int(i));
            buffer->put_non_bloccante(buffer, message);
            int* contentPtr = static_cast<int*>(message->getContent());
            int contentValue = *contentPtr;
            std::cout << "\nProducer " << producer_id << " pushed message -->" <<contentValue<< std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "producer " << producer_id << " encountered an exception: " << e.what() << std::endl;
    }
}

void consumer(buffer_t *buffer, int consumer_id,int numMessage) {
    try {
        for (int i = 0; i < numMessage; i++) {
            msg_t *message = buffer->get_non_bloccante(buffer);
            int *contentPtr = static_cast<int *>(message->getContent());
            int contentValue = *contentPtr;
            std::cout << "\nConsumer " << consumer_id << " popped message -->" << contentValue << std::endl;
            delete message;
        }
    }catch (const std::exception& e) {
            std::cerr << "Consumer " << consumer_id << " encountered an exception: " << e.what() << std::endl;
        }
    }
