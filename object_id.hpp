#ifndef OBJECT_ID_HPP
#define OBJECT_ID_HPP
#include <iostream>


namespace cppplayground {
   struct ObjectId {
     explicit  ObjectId(int id) : obj_id(id) {
       std::cout << "Object(" << std::addressof(*this) << ") Constructed: " << obj_id << std::endl;
     }

     ObjectId(const ObjectId& other) : obj_id(other.obj_id) {
       std::cout << "Object(" << std::addressof(*this) << ") Copy Constructed: " << obj_id << std::endl;
     }

     ObjectId(ObjectId&& other) : obj_id(other.obj_id) {
       std::cout << "Object(" << std::addressof(*this) << ") Move Constructed: " << obj_id << std::endl;
     }

     ObjectId& operator=(const ObjectId& other) {
       std::cout << "Object(" << std::addressof(*this) << ") Assigned: " << obj_id << " <=== " << other.obj_id << std::endl;
       obj_id = other.obj_id;
       return *this;
     }

     ObjectId& operator=(ObjectId&& other) {
       std::cout << "Object(" << std::addressof(*this) << ") Move Assigned: " << obj_id << " <=== " << other.obj_id << std::endl;
       obj_id = other.obj_id;
       return *this;
     }

     ~ObjectId() {
       std::cout << "Object(" << std::addressof(*this) << ") Destructed: " << obj_id << std::endl;
     }

     int obj_id;
   };
} // end namespace

#endif