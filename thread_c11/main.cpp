//
//  main.cpp
//  thread_c11
//
//  Created by txh on 2017/6/14.
//  Copyright © 2017年 txh. All rights reserved.
//

#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <stdexcept>
#include <future>
#include <condition_variable>
#include <atomic>
#include <vector>
#include <sstream>
using namespace std;

mutex m;
void f1(int n)
{
    for (int i = 0 ; i < 5 ; i++) {
        m.lock();
        cout << "thread1 "<< n << " \n" << endl;
        m.unlock();
        this_thread::sleep_for(chrono::milliseconds(10));
    }
}

void f2(int &n)
{
    for (int i = 0; i <5 ; i++) {
        m.try_lock();
        cout << "thread2  " << n <<" \n" << endl;
        m.unlock();
        n++;
        this_thread::sleep_for(chrono::milliseconds(10));
    }
}

volatile int iCount = 0;
void f3()
{
    for (int i = 0 ; i < 10000 ; i++) {
        m.lock();
            iCount++;
            m.unlock();
        
    }
}

void printEven(int i)
{
    if (i % 2 == 0) {
        cout << "even" << endl;
    }
    else
    {
        throw logic_error("not even");
    }
}

void f4(int n)
{
    try{
        unique_lock<mutex> lg(m);
        printEven(n);
    }
    catch(logic_error &)
    {
        cout << "except catch" << endl;
    }
    
}

void f5(int n)
{
    m.lock();
    lock_guard<mutex> lg(m,adopt_lock);
    for (int i = 0 ; i < 5 ; i++) {
        printEven(2);
    }
    cout << this_thread::get_id() << endl;
}

mutex foo,bar;

void f6(int n)
{
    lock(foo, bar);
    unique_lock<mutex> uf(foo,adopt_lock);
    unique_lock<mutex> ub(bar,adopt_lock);
    
//    uf.release()->unlock();
    
    cout << __func__ << endl;
}

void f7(int n)
{
    
    unique_lock<mutex> uf,ub;
    uf = unique_lock<mutex>(foo,defer_lock);
    ub = unique_lock<mutex>(bar,defer_lock);
    lock(uf, ub);
    cout << __func__ << endl;
}

void f8(future<int> &fut)
{
    int x = fut.get();
    cout << __func__ << " " << x << endl;
}

promise<int> gProm;

void f9()
{
    future<int> fut = gProm.get_future();
    int x = fut.get();
    cout << __func__ << " " << x << endl;
}

void getInt(promise<int> &prom)
{
    int x;
    cin.exceptions(ios::failbit);
    try {
        cin >> x;
        prom.set_value(x);
    } catch (exception &) {
        prom.set_exception(current_exception());
    }
}

void printInt(future<int> &fut)
{
    try {
        int x = fut.get();
        cout << "get " << x << endl;
    } catch (exception & e) {
        cout << "exception " << e.what() << endl;
    }
}

int countDown(int from, int to)
{
    for (int i = from ; i >= to ; i--) {
        cout << i << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }
    cout << "finish " << endl;
    return from - to;
}

future<int> f10(packaged_task<int(int)> &task,int value)
{
    if (task.valid()) {
        future<int> ret = task.get_future();
        thread(move(task),value).detach();
        return ret;
    }
    else
        return future<int>();
}

bool isPrime(int x)
{
    for (int i = 2 ; i < x; ++i) {
        if (x % 2 == 0) {
            return false;
        }
    }
    return true;
}

condition_variable cv;
void do_print_id(int i)
{
    unique_lock<mutex> lck(m);
    cv.wait(lck);
    cout << i << " running " << endl;
}

void go()
{
    unique_lock<mutex> lck(m);
    cv.notify_all();
}

int cargo = 0;
bool hasCargo()
{
    return cargo;
}

void comsume(int n)
{
    unique_lock<mutex> lck(m);
    for (int i = 0; i < n; ++i) {
        cv.wait(lck, hasCargo);
        cargo = 0;
    }
}

void produce()
{
    for (int i = 0; i < 10; i++) {
        while (hasCargo()) {
            this_thread::yield();
        }
        unique_lock<mutex> lck(m);
        cargo++;
        cv.notify_one();
    }
}


int value;

void getValue()
{
    cin >> value;
    cv.notify_one();
}


atomic<bool> isReady(false);
atomic_flag af = ATOMIC_FLAG_INIT;

void count1m(int id)
{
    while (!isReady) {
        this_thread::yield();
    }
    
    for (int i = 0; i < 100000; i++) {
    }
    
    if (!af.test_and_set()) {
        cout << "first one " << id << endl;
    }
}


stringstream ss;


int main(int argc, const char * argv[]) {
    
    vector<thread> ts;
    for (int i = 0; i < 10; ++i) {
        ts.emplace_back(thread([](int i){
            while (af.test_and_set()) {
                this_thread::yield();
            }
            ss << "thread #" << i << endl;
            af.clear();
        },
        i));
    }

    
    for (auto &t : ts) {
        t.join();
    }
    cout << ss.str() << endl;

    return 0;
}

