#ifndef SINGLETON_H_
#define SINGLETON_H_

template<typename T> class Singleton {
  public:
  static T& Instance() {
    static T theSingleInstance;
    return theSingleInstance;
  }
};

#endif  // SINGLETON_H_
