#include "main.h"

void ThreadingExample()
{
  //this will be JUST AN EXAMPLE on how our threading system works
  /**

  For context, threading is a system where you can run multiple functions(on multiple "threads") at the SAME TIME
  Ex. if I want to move forward AND pick up a frisbee at the same time, the way I would do that is through threading

  the way we do it is such


  std::map<std::string, std::unique_ptr<pros::Task>> tasks;
  ^^
  what that does is it makes a list of PROS tasks mapped to a key(basically in a HashMap/Dictionary)
  unique_ptrs are a c++ thing that basically allows for object destruction with pointer destruction
  Ex. if I have a String pointer(string*) x, and I made it a unique_pointer, what would happen is that, whenever x goes out of scope
  or whenever a reset function is called to it, it destroys the original object that it is pointing to. This makes it very efficient for memory purposes

  tasks are a thing that pros does to make multithreading easy
  to make a function run on a side-thread(basically a thread off the main thread(opcontrol) that runs in conjunction with it)

  these are common functions that go along with it

  void start_task(std::string name, void (*func)(void *)) {
    if (!task_exists(name)) {
        tasks.insert(std::pair<std::string, std::unique_ptr<pros::Task>>(name, std::move(std::make_unique<pros::Task>(func, &x, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, ""))));
    }
  }
  bool task_exists(std::string name) {
      return tasks.find(name) != tasks.end();
  }

  void kill_task(std::string name) {
      if (task_exists(name)) {
          tasks.erase(name);
      }
  }

  and yes, you do literally pass in function names that are of the signature name(void*) into start_task lol
  and &x can and should be a RNGed number: we just don't know what any of it does so...
  **/
}
