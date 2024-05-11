#include <string>
#ifndef LIGHTS_HPP
#define LIGHTS_HPP

typedef enum class LightType;
typedef struct lights* Lights;

Lights novaLight();
std::string getType(Lights l);
void setType(Lights l, std::string type);
float getPosX(Lights l);
void setPosX(Lights l, float posx);
float getPosY(Lights l);
void setPosY(Lights l, float posy);
float getPosZ(Lights l);
void setPosZ(Lights l, float posz);
float getDirX(Lights l);
void setDirX(Lights l, float dirx);
float getDirY(Lights l);
void setDirY(Lights l, float diry);
float getDirZ(Lights l);
void setDirZ(Lights l, float dirz);
float getCutoff(Lights l);
void setCutoff(Lights l, float cutoff);

#endif