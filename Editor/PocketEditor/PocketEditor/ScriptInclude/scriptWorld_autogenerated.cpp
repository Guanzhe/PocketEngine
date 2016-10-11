namespace Pocket {
struct Transform;
struct Mesh;
struct Material;
struct Camera;
struct TextureComponent;
struct Orderable;
struct Touchable;
struct Cloner;
struct Turner;
struct EditorObject;
struct InputMapper;
struct InputController;
}
struct Collidable;
struct Controller;
struct Velocity;

#include "GameSystem.hpp"
template<> Pocket::Transform* Pocket::GameObject::GetComponent<Pocket::Transform>() { return (Pocket::Transform*) GetComponent(0); }
template<> Pocket::Transform* Pocket::GameObject::AddComponent<Pocket::Transform>() { AddComponent(0); return (Pocket::Transform*) GetComponent(0); }
template<> void Pocket::GameObject::RemoveComponent<Pocket::Transform>() { RemoveComponent(0); }
template<> Pocket::Transform* Pocket::GameObject::CloneComponent<Pocket::Transform>(GameObject* source) { CloneComponent(0, source); return (Pocket::Transform*) GetComponent(0); }
template<> Pocket::Mesh* Pocket::GameObject::GetComponent<Pocket::Mesh>() { return (Pocket::Mesh*) GetComponent(1); }
template<> Pocket::Mesh* Pocket::GameObject::AddComponent<Pocket::Mesh>() { AddComponent(1); return (Pocket::Mesh*) GetComponent(1); }
template<> void Pocket::GameObject::RemoveComponent<Pocket::Mesh>() { RemoveComponent(1); }
template<> Pocket::Mesh* Pocket::GameObject::CloneComponent<Pocket::Mesh>(GameObject* source) { CloneComponent(1, source); return (Pocket::Mesh*) GetComponent(1); }
template<> Pocket::Material* Pocket::GameObject::GetComponent<Pocket::Material>() { return (Pocket::Material*) GetComponent(2); }
template<> Pocket::Material* Pocket::GameObject::AddComponent<Pocket::Material>() { AddComponent(2); return (Pocket::Material*) GetComponent(2); }
template<> void Pocket::GameObject::RemoveComponent<Pocket::Material>() { RemoveComponent(2); }
template<> Pocket::Material* Pocket::GameObject::CloneComponent<Pocket::Material>(GameObject* source) { CloneComponent(2, source); return (Pocket::Material*) GetComponent(2); }
template<> Pocket::Camera* Pocket::GameObject::GetComponent<Pocket::Camera>() { return (Pocket::Camera*) GetComponent(3); }
template<> Pocket::Camera* Pocket::GameObject::AddComponent<Pocket::Camera>() { AddComponent(3); return (Pocket::Camera*) GetComponent(3); }
template<> void Pocket::GameObject::RemoveComponent<Pocket::Camera>() { RemoveComponent(3); }
template<> Pocket::Camera* Pocket::GameObject::CloneComponent<Pocket::Camera>(GameObject* source) { CloneComponent(3, source); return (Pocket::Camera*) GetComponent(3); }
template<> Pocket::TextureComponent* Pocket::GameObject::GetComponent<Pocket::TextureComponent>() { return (Pocket::TextureComponent*) GetComponent(4); }
template<> Pocket::TextureComponent* Pocket::GameObject::AddComponent<Pocket::TextureComponent>() { AddComponent(4); return (Pocket::TextureComponent*) GetComponent(4); }
template<> void Pocket::GameObject::RemoveComponent<Pocket::TextureComponent>() { RemoveComponent(4); }
template<> Pocket::TextureComponent* Pocket::GameObject::CloneComponent<Pocket::TextureComponent>(GameObject* source) { CloneComponent(4, source); return (Pocket::TextureComponent*) GetComponent(4); }
template<> Pocket::Orderable* Pocket::GameObject::GetComponent<Pocket::Orderable>() { return (Pocket::Orderable*) GetComponent(5); }
template<> Pocket::Orderable* Pocket::GameObject::AddComponent<Pocket::Orderable>() { AddComponent(5); return (Pocket::Orderable*) GetComponent(5); }
template<> void Pocket::GameObject::RemoveComponent<Pocket::Orderable>() { RemoveComponent(5); }
template<> Pocket::Orderable* Pocket::GameObject::CloneComponent<Pocket::Orderable>(GameObject* source) { CloneComponent(5, source); return (Pocket::Orderable*) GetComponent(5); }
template<> Pocket::Touchable* Pocket::GameObject::GetComponent<Pocket::Touchable>() { return (Pocket::Touchable*) GetComponent(7); }
template<> Pocket::Touchable* Pocket::GameObject::AddComponent<Pocket::Touchable>() { AddComponent(7); return (Pocket::Touchable*) GetComponent(7); }
template<> void Pocket::GameObject::RemoveComponent<Pocket::Touchable>() { RemoveComponent(7); }
template<> Pocket::Touchable* Pocket::GameObject::CloneComponent<Pocket::Touchable>(GameObject* source) { CloneComponent(7, source); return (Pocket::Touchable*) GetComponent(7); }
template<> Pocket::Cloner* Pocket::GameObject::GetComponent<Pocket::Cloner>() { return (Pocket::Cloner*) GetComponent(27); }
template<> Pocket::Cloner* Pocket::GameObject::AddComponent<Pocket::Cloner>() { AddComponent(27); return (Pocket::Cloner*) GetComponent(27); }
template<> void Pocket::GameObject::RemoveComponent<Pocket::Cloner>() { RemoveComponent(27); }
template<> Pocket::Cloner* Pocket::GameObject::CloneComponent<Pocket::Cloner>(GameObject* source) { CloneComponent(27, source); return (Pocket::Cloner*) GetComponent(27); }
template<> Pocket::Turner* Pocket::GameObject::GetComponent<Pocket::Turner>() { return (Pocket::Turner*) GetComponent(28); }
template<> Pocket::Turner* Pocket::GameObject::AddComponent<Pocket::Turner>() { AddComponent(28); return (Pocket::Turner*) GetComponent(28); }
template<> void Pocket::GameObject::RemoveComponent<Pocket::Turner>() { RemoveComponent(28); }
template<> Pocket::Turner* Pocket::GameObject::CloneComponent<Pocket::Turner>(GameObject* source) { CloneComponent(28, source); return (Pocket::Turner*) GetComponent(28); }
template<> Pocket::EditorObject* Pocket::GameObject::GetComponent<Pocket::EditorObject>() { return (Pocket::EditorObject*) GetComponent(29); }
template<> Pocket::EditorObject* Pocket::GameObject::AddComponent<Pocket::EditorObject>() { AddComponent(29); return (Pocket::EditorObject*) GetComponent(29); }
template<> void Pocket::GameObject::RemoveComponent<Pocket::EditorObject>() { RemoveComponent(29); }
template<> Pocket::EditorObject* Pocket::GameObject::CloneComponent<Pocket::EditorObject>(GameObject* source) { CloneComponent(29, source); return (Pocket::EditorObject*) GetComponent(29); }
template<> Pocket::InputMapper* Pocket::GameObject::GetComponent<Pocket::InputMapper>() { return (Pocket::InputMapper*) GetComponent(30); }
template<> Pocket::InputMapper* Pocket::GameObject::AddComponent<Pocket::InputMapper>() { AddComponent(30); return (Pocket::InputMapper*) GetComponent(30); }
template<> void Pocket::GameObject::RemoveComponent<Pocket::InputMapper>() { RemoveComponent(30); }
template<> Pocket::InputMapper* Pocket::GameObject::CloneComponent<Pocket::InputMapper>(GameObject* source) { CloneComponent(30, source); return (Pocket::InputMapper*) GetComponent(30); }
template<> Pocket::InputController* Pocket::GameObject::GetComponent<Pocket::InputController>() { return (Pocket::InputController*) GetComponent(31); }
template<> Pocket::InputController* Pocket::GameObject::AddComponent<Pocket::InputController>() { AddComponent(31); return (Pocket::InputController*) GetComponent(31); }
template<> void Pocket::GameObject::RemoveComponent<Pocket::InputController>() { RemoveComponent(31); }
template<> Pocket::InputController* Pocket::GameObject::CloneComponent<Pocket::InputController>(GameObject* source) { CloneComponent(31, source); return (Pocket::InputController*) GetComponent(31); }
template<> Collidable* Pocket::GameObject::GetComponent<Collidable>() { return (Collidable*) GetComponent(32); }
template<> Collidable* Pocket::GameObject::AddComponent<Collidable>() { AddComponent(32); return (Collidable*) GetComponent(32); }
template<> void Pocket::GameObject::RemoveComponent<Collidable>() { RemoveComponent(32); }
template<> Collidable* Pocket::GameObject::CloneComponent<Collidable>(GameObject* source) { CloneComponent(32, source); return (Collidable*) GetComponent(32); }
template<> Controller* Pocket::GameObject::GetComponent<Controller>() { return (Controller*) GetComponent(33); }
template<> Controller* Pocket::GameObject::AddComponent<Controller>() { AddComponent(33); return (Controller*) GetComponent(33); }
template<> void Pocket::GameObject::RemoveComponent<Controller>() { RemoveComponent(33); }
template<> Controller* Pocket::GameObject::CloneComponent<Controller>(GameObject* source) { CloneComponent(33, source); return (Controller*) GetComponent(33); }
template<> Velocity* Pocket::GameObject::GetComponent<Velocity>() { return (Velocity*) GetComponent(34); }
template<> Velocity* Pocket::GameObject::AddComponent<Velocity>() { AddComponent(34); return (Velocity*) GetComponent(34); }
template<> void Pocket::GameObject::RemoveComponent<Velocity>() { RemoveComponent(34); }
template<> Velocity* Pocket::GameObject::CloneComponent<Velocity>(GameObject* source) { CloneComponent(34, source); return (Velocity*) GetComponent(34); }
class IGameSystem;
#include "TypeInfo.hpp"
#include "Property.hpp"
#include "Transform.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Mesh.hpp"
#include "Sizeable.hpp"
#include "VertexMesh.hpp"
#include "TextureAtlas.hpp"
#include "Colour.hpp"
#include "Touchable.hpp"
#include "InputController.hpp"
#include "Collidable.cpp"
#include "Controller.cpp"
#include "Velocity.cpp"
#include "VelocityCollider.cpp"

#include <string>
#include <vector>
#include "Property.hpp"
template<> struct Pocket::FieldInfoIndexer<bool> { static int Index() { return 0; } };
template<> struct Pocket::FieldInfoIndexer<std::vector<bool>> { static int Index() { return 1; } };
template<> struct Pocket::FieldInfoIndexer<Pocket::Property<bool>> { static int Index() { return 2; } };
template<> struct Pocket::FieldInfoIndexer<int> { static int Index() { return 3; } };
template<> struct Pocket::FieldInfoIndexer<std::vector<int>> { static int Index() { return 4; } };
template<> struct Pocket::FieldInfoIndexer<Pocket::Property<int>> { static int Index() { return 5; } };
template<> struct Pocket::FieldInfoIndexer<float> { static int Index() { return 6; } };
template<> struct Pocket::FieldInfoIndexer<std::vector<float>> { static int Index() { return 7; } };
template<> struct Pocket::FieldInfoIndexer<Pocket::Property<float>> { static int Index() { return 8; } };
template<> struct Pocket::FieldInfoIndexer<double> { static int Index() { return 9; } };
template<> struct Pocket::FieldInfoIndexer<std::vector<double>> { static int Index() { return 10; } };
template<> struct Pocket::FieldInfoIndexer<Pocket::Property<double>> { static int Index() { return 11; } };
template<> struct Pocket::FieldInfoIndexer<std::__1::basic_string<char>> { static int Index() { return 12; } };
template<> struct Pocket::FieldInfoIndexer<std::vector<std::__1::basic_string<char>>> { static int Index() { return 13; } };
template<> struct Pocket::FieldInfoIndexer<Pocket::Property<std::__1::basic_string<char> >> { static int Index() { return 14; } };
template<> struct Pocket::FieldInfoIndexer<Pocket::Vector3> { static int Index() { return 15; } };
template<> struct Pocket::FieldInfoIndexer<std::vector<Pocket::Vector3>> { static int Index() { return 16; } };
template<> struct Pocket::FieldInfoIndexer<Pocket::Property<Pocket::Vector3>> { static int Index() { return 17; } };

extern "C" int CountSystems() {
   return 4;
}
extern "C" IGameSystem* CreateSystem(int systemID) {
   switch (systemID) { 
      case 38: return new CollisionSystem();
      case 39: return new ControllerSystem();
      case 40: return new VelocityCollider();
      case 41: return new VelocitySystem();
      default: return 0;
   }
}
extern "C" void DeleteSystem(IGameSystem* scriptSystem) {
   delete scriptSystem; 
}
extern "C" int CountComponents() {
   return 3;
}
extern "C" void* CreateComponent(int componentID) {
   switch (componentID) { 
      case 32: return new Collidable();
      case 33: return new Controller();
      case 34: return new Velocity();
      default: return 0;
   }
}
extern "C" void DeleteComponent(int componentID, void* component) {
   switch (componentID) { 
      case 32: { delete ((Collidable*)component); break; }
      case 33: { delete ((Controller*)component); break; }
      case 34: { delete ((Velocity*)component); break; }
   }
}
extern "C" void ResetComponent(int componentID, void* c, void* s) {
   switch (componentID) { 
      case 32: { Collidable* co = (Collidable*)c; 
      Collidable* so = ((Collidable*)s);
        co->operator=(*so);             break; }
      case 33: { Controller* co = (Controller*)c; 
      Controller* so = ((Controller*)s);
        co->operator=(*so);             break; }
      case 34: { Velocity* co = (Velocity*)c; 
      Velocity* so = ((Velocity*)s);
        co->operator=(*so);             break; }
   }
}

extern "C" Pocket::TypeInfo* GetTypeInfo(int componentID, void* componentPtr) {
   switch (componentID) { 
      case 32: {
      Collidable* component = (Collidable*)componentPtr;
	      Pocket::TypeInfo* info = new Pocket::TypeInfo();
	      info->name = "Collidable";
	      info->AddField(component->radius, "radius");
      return info;
      break; }
      case 33: {
      Controller* component = (Controller*)componentPtr;
	      Pocket::TypeInfo* info = new Pocket::TypeInfo();
	      info->name = "Controller";
	      info->AddField(component->downKey, "downKey");
	      info->AddField(component->speed, "speed");
	      info->AddField(component->upKey, "upKey");
      return info;
      break; }
      case 34: {
      Velocity* component = (Velocity*)componentPtr;
	      Pocket::TypeInfo* info = new Pocket::TypeInfo();
	      info->name = "Velocity";
	      info->AddField(component->velocity, "velocity");
      return info;
      break; }
      default: return 0;
   }
}
extern "C" void DeleteTypeInfo(Pocket::TypeInfo* typeInfo) {
delete typeInfo;
}
