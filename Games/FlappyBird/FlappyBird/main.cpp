#include "Engine.hpp"
#include "GameWorld.hpp"
#include "RenderSystem.hpp"
#include "Transform.hpp"
#include "VelocitySystem.hpp"
#include "TransformHierarchy.hpp"
#include "Span.hpp"
#include "Sizeable.hpp"
#include "MathHelper.hpp"

using namespace Pocket;

Component(Flappable)
    float force;
};

Component(Gravity)
    float gravity;
};

SYSTEM(GravitySystem, Velocity, Gravity)
    void Update(float dt) {
        for (auto o : Objects()) {
            o->GetComponent<Velocity>()->velocity += Vector3(0,-o->GetComponent<Gravity>()->gravity,0) * dt;
        }
    }
};

SYSTEM(FlappySystem, Flappable, Velocity)
public:
    void SetInput(InputManager* input) {
        input->ButtonDown += event_handler(this, &FlappySystem::ButtonDown);
    }

    void ButtonDown(std::string button) {
        if (button == " ") {
            buttonDown = true;
        }
    }

    void Update(float dt) {
        if (!buttonDown) return;
        buttonDown = false;
        for(auto o : Objects()) {
            Vector3 vel = o->GetComponent<Velocity>()->velocity;
            vel.y = o->GetComponent<Flappable>()->force;
            o->GetComponent<Velocity>()->velocity = vel;
        }
    }

    bool buttonDown;
};

Component(Background)
    float parallax;
    Vector2 size;
};

SYSTEM(BackgroundSystem, Background, Transform, Mesh)
    void Update(float dt) {
        for(auto o : Objects()) {
            
            Background* background = o->GetComponent<Background>();
            Transform* transform = o->GetComponent<Transform>();
            Mesh* mesh = o->GetComponent<Mesh>();
            
            if (mesh->Vertices().size() == 0) {
                mesh->AddQuad(0, background->size, Colour::White());
                SwapV(mesh->Vertices(), 0, 3);
                SwapV(mesh->Vertices(), 1, 2);
            }
            
            Mesh::VerticesList& verts = mesh->Vertices();
            
            Matrix4x4 world = *transform->World.GetValue();
            world *= Matrix4x4::CreateTransform({world.Translation().x*background->parallax,0,0}, 1, Quaternion::IDENTITY);
            Vector3 leftEdge = world.TransformPosition(-background->size);
            Vector3 rightEdge = world.TransformPosition(background->size);
            
            leftEdge /= background->size;
            rightEdge /= background->size;
            
            verts[0].TextureCoords.x = leftEdge.x;
            verts[3].TextureCoords.x = leftEdge.x;
            
            verts[1].TextureCoords.x = rightEdge.x;
            verts[2].TextureCoords.x = rightEdge.x;
            
        }
    }

    void SwapV(Mesh::VerticesList& v, int a, int b) {
        float t = v[a].TextureCoords.y;
        v[a].TextureCoords.y = v[b].TextureCoords.y;
        v[b].TextureCoords.y = t;
    }

};

Component(VelocityRotator)
    float LerpSpeed;
};

SYSTEM(VelocityRotatorSystem, VelocityRotator, Velocity, Transform)
    void Update(float dt) {
        for(auto o : Objects()) {
            Vector3 vel = o->GetComponent<Velocity>()->velocity;
            float rotation = atan2f(vel.y, vel.x);
            Quaternion rot = o->GetComponent<Transform>()->Rotation;
            rot.Normalize();
            Quaternion target = Quaternion(rotation);
            Quaternion quat = Quaternion::SlerpExtraSpins(o->GetComponent<VelocityRotator>()->LerpSpeed*dt, rot, target, 0);
            quat.Normalize();
            o->GetComponent<Transform>()->Rotation = quat;
        }
    }
};

Component(PipeSpawner)
    void Reset() {
        offset = 1.0f;
        spawnDistance = 2.0f;
        lastSpawnX = 0;
    }
    float nextSpawner;
    float offset;
    float spawnDistance;
    float lastSpawnX;
    Span<float> openHeight;
    Span<float> yOffset;
};

SYSTEM(PipeSpawnerSystem, PipeSpawner, Transform, Sizeable)
public:

    GameObject* texture;
    void AddedToWorld(GameWorld& world) {
        
    }

    void Update(float dt) {
        for (auto o : Objects()) {
            PipeSpawner* pipeSpawner = o->GetComponent<PipeSpawner>();
            float fromLast = o->GetComponent<Transform>()->Position().x - pipeSpawner->lastSpawnX;
            
            if (fromLast>pipeSpawner->spawnDistance) {
            	Vector2 size = o->GetComponent<Sizeable>()->Size;
            
                pipeSpawner->lastSpawnX = o->GetComponent<Transform>()->Position().x;
                Transform* transform = o->GetComponent<Transform>();
                Vector3 topPosition = transform->World.GetValue()->TransformPosition(Vector3(pipeSpawner->offset,size.y,0));
                Vector3 bottomPosition = transform->World.GetValue()->TransformPosition(Vector3(pipeSpawner->offset,0,0));
                topPosition.z = 0;
                bottomPosition.z = 0;
                
                float yOffset = pipeSpawner->yOffset.Get(MathHelper::Random());
                
                Vector3 centerPosition = (topPosition + bottomPosition) * 0.5f + Vector3(0,yOffset,0);
                
                float height = pipeSpawner->openHeight.Get(MathHelper::Random());
                
                Vector3 topEdge = centerPosition + Vector3(0,height*0.5f,0);
                Vector3 bottomEdge = centerPosition - Vector3(0,height*0.5f,0);
                
                float topHeight = topPosition.y - topEdge.y;
                float bottomHeight = bottomEdge.y - bottomPosition.y;
                
                {
                GameObject* pipe = World()->CreateObject();
                pipe->AddComponent<Transform>()->Position = topPosition;
                pipe->GetComponent<Transform>()->Anchor = {0,topHeight*0.5f,0};
                pipe->AddComponent<Mesh>()->AddQuad(0, {0.2f,topHeight}, Colour::White());
                pipe->AddComponent<Material>()->BlendMode = BlendMode::Alpha;
                pipe->AddComponent<TextureComponent>(texture);
                }
                
                {
                GameObject* pipe = World()->CreateObject();
                pipe->AddComponent<Transform>()->Position = bottomPosition;
                pipe->GetComponent<Transform>()->Anchor = {0,-bottomHeight*0.5f,0};
                pipe->AddComponent<Mesh>()->AddQuad(0, {0.2f,bottomHeight}, Colour::White());
                Mesh::VerticesList& verts = pipe->GetComponent<Mesh>()->Vertices();
                SwapV(verts, 0, 3);
                SwapV(verts, 1, 2);
                pipe->AddComponent<Material>()->BlendMode = BlendMode::Alpha;
                pipe->AddComponent<TextureComponent>(texture);
                }
            }
        }
    }

    void SwapV(Mesh::VerticesList& v, int a, int b) {
        float t = v[a].TextureCoords.y;
        v[a].TextureCoords.y = v[b].TextureCoords.y;
        v[b].TextureCoords.y = t;
    }
};


class Game : public GameState<Game> {
public:
    GameWorld world;
    GameObject* camera;
    GameObject* bird;
    GameObject* backgroundTexture;
    Vector2 screenSize;
    
    void Initialize() {
        
        world.CreateSystem<GravitySystem>();
        world.CreateSystem<FlappySystem>()->SetInput(&Input);
        world.CreateSystem<VelocitySystem>();
        world.CreateSystem<VelocityRotatorSystem>();
        world.CreateSystem<TransformHierarchy>();
        world.CreateSystem<BackgroundSystem>();
        PipeSpawnerSystem* pipeSpawnerSystem = world.CreateSystem<PipeSpawnerSystem>();
        world.CreateSystem<RenderSystem>();
        
        
        backgroundTexture = world.CreateObject();
        backgroundTexture->AddComponent<TextureComponent>()->Texture().LoadFromPng("bg.png");
        
        pipeSpawnerSystem->texture = world.CreateObject();
        pipeSpawnerSystem->texture->AddComponent<TextureComponent>()->Texture().LoadFromPng("pipe.png");
        
        screenSize = {1.0f * Manager().ScreenSize().Aspect(),1.0f};
        
        camera = world.CreateObject();
        
        camera->AddComponent<Camera>()->Viewport = Box(0,screenSize.y, screenSize.x, 0);
        camera->AddComponent<Transform>()->Position = { 0, 0, 1 };
        camera->GetComponent<Camera>()->Orthographic = true;
        camera->GetComponent<Camera>()->Near = 0.5f;
        camera->GetComponent<Camera>()->Far = 10.0f;
        
        Vector2 birdPixelSize(17,12);
        
        bird = world.CreateObject();
        bird->AddComponent<Transform>()->Position = {0.5f,0.5f,0};
        bird->AddComponent<Mesh>()->AddCube(0, {0.03f*birdPixelSize.Aspect(),0.03f,0.01f});
        bird->AddComponent<Material>();
        bird->AddComponent<Velocity>()->velocity = {0.35f,0,0};
        bird->AddComponent<Gravity>()->gravity = 2.20f;
        bird->AddComponent<Flappable>()->force = 0.85f;
        bird->AddComponent<VelocityRotator>()->LerpSpeed = 8.0f;
        bird->AddComponent<TextureComponent>()->Texture().LoadFromPng("Bird.png");
        bird->GetComponent<Material>()->BlendMode = BlendMode::Alpha;
        
        GameObject* background = world.CreateObject();
        background->Parent = camera;
        background->AddComponent<Transform>()->Position = {screenSize.x*0.5f,screenSize.y*0.5f,-2};
        auto b = background->AddComponent<Background>();
        b->parallax = 0.002f;
        b->size = screenSize;
        background->AddComponent<Mesh>();
        background->AddComponent<Material>();
        background->AddComponent<TextureComponent>(backgroundTexture);
        
        GameObject* pipeSpawner = world.CreateObject();
        pipeSpawner->AddComponent<PipeSpawner>()->offset = screenSize.x + 0.1f;
        pipeSpawner->GetComponent<PipeSpawner>()->spawnDistance = 0.6f;
        pipeSpawner->GetComponent<PipeSpawner>()->openHeight = {0.3f,0.3f};
        pipeSpawner->GetComponent<PipeSpawner>()->yOffset = {-0.3f,0.3f};
        
        
        pipeSpawner->AddComponent<Transform>(camera);
        pipeSpawner->AddComponent<Sizeable>()->Size = screenSize;
        
        
        Input.ButtonUp += event_handler(this, &Game::ButtonUp);
    }
    
    void ButtonUp(std::string button) {
        if (button == "\e") {
            exit(0);
        }
    }
    
    void Update(float dt) {
        world.Update(dt);
        Vector3 birdPosition = bird->GetComponent<Transform>()->Position;
        birdPosition.y = 0;
        camera->GetComponent<Transform>()->Position = birdPosition + Vector3(-screenSize.x*0.5f, -screenSize.y*0.5f,1);
    }
    
    void Render() {
        world.Render();
    }
};

int main() {
    Engine e;
    e.Start<Game>();
	return 0;
}