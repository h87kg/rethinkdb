
#ifndef __FSM_HPP__
#define __FSM_HPP__

#include "arch/common.hpp"
#include "containers/intrusive_list.hpp"
#include "common.hpp"

struct event_state_t {
    resource_t source;
};

// The states are collected via an intrusive list
struct fsm_state_t;
typedef intrusive_list_node_t<fsm_state_t> fsm_list_node_t;
typedef intrusive_list_t<fsm_state_t> fsm_list_t;

// Define the state structure
struct fsm_state_t : public event_state_t, public fsm_list_node_t {
    enum state_t {
        fsm_socket_connected,
        fsm_socket_recv_incomplete
    };
    state_t state;

    // A buffer with IO communication (possibly incomplete). The nbuf
    // variable indicates how many bytes are stored in the buffer.
    char *buf;
    unsigned int nbuf;
};

struct event_queue_t;
struct event_t;

void fsm_init_state(fsm_state_t *state);
void fsm_destroy_state(fsm_state_t *state, event_queue_t *event_queue);

void fsm_do_transition(event_queue_t *event_queue, event_t *event);

#endif // __FSM_HPP__

