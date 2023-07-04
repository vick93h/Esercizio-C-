//
// Created by vitto on 03/07/2023.
//

#include "msg_t.h"
msg_t::msg_t() : content(nullptr) {}
msg_t* msg_t::msg_init(void *content_) {
    content=content_;
    return static_cast<msg_t *>(content);
}
void msg_t::msg_destroy(msg_t *msg){
    content=msg;
    delete content;
    content= nullptr;
}