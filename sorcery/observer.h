#ifndef observer_hpp
#define observer_hpp

class Subject;

class Observer {
public:
    virtual void notify() = 0;
    virtual ~Observer() = default;
};

#endif /* observer_hpp */
