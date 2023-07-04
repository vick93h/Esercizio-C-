//
// Created by vitto on 03/07/2023.
//

#include "msg_t.h"
msg_t::msg_t() : content(nullptr) {}
msg_t::msg_t(void* content_) : content(content_) {}
void* msg_t::msg_init(void *content_) {
    content=content_;
    return (content);
}
void msg_t::msg_destroy(msg_t *msg){
    content=msg;
    delete content;
    content= nullptr;
}

void *msg_t::getContent() const {
    return content;
}

void msg_t::setContent(void *content) {
    msg_t::content = content;
}
