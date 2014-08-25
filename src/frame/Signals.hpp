// Copyright [2014] By Stett ...
// ... to make his whiny-ass linter shut up about friggin' copyrights.

#pragma once
#include <typeindex>
#include <typeinfo>
#include <memory>
#include <set>
using std::type_index;
using std::shared_ptr;
using std::set;


namespace frame {

    class Signal {
    public:
        Signal() {}
        virtual ~Signal() {}
    };


    class SignalManager;
    class Signals {
        friend class SignalManager;

    protected:
        set<SignalManager*> signal_managers;

    public:
        void add_signal_manager(SignalManager* signal_manager) {
            signal_managers.insert(signal_manager);
        }
    };


    class SignalManager {
    protected:
        shared_ptr<Signals> signals;
    public:
        SignalManager() : signals(0) {}
        virtual ~SignalManager() {}

        void set_signals(shared_ptr<Signals> signals) {
            if (this->signals) this->signals->signal_managers.erase(this);
            this->signals = signals;
            signals->signal_managers.insert(this);
        }

        virtual void handle_signal(shared_ptr<Signal> signal, type_index type) {}

        template <typename T>
        void dispatch(T* signal) {
            dispatch(signal, type_index(typeid(T)));
        }

        void dispatch(Signal* signal, type_index type) {
            if (signals)
                for (auto signal_manager : signals->signal_managers)
                    if (signal_manager != this)
                        signal_manager->handle_signal(shared_ptr<Signal>(signal), type);
        }
    };
}
