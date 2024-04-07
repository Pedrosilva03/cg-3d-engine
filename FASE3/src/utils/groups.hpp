#include <list>
#include <string>
#ifndef GROUPS_HPP
#define GROUPS_HPP


typedef struct group* Group;

typedef struct transform* Transform;

typedef enum class TransformType;

Group novoGrupo();

Group getChild(Group g, int i);
std::list<Transform> getTransform(Group g);
std::list<std::string> getFiles(Group g);
void add_transform(Group node, std::list<Transform> transfrom_node);
void add_node(Group node, Group child_node);
void push_file(Group group, std::string file);

Transform novoTransform();

void add_transformType(Transform t, const char* type);
void add_transformAngle(Transform t, float angle);
void add_transformX(Transform t, float x);
void add_transformY(Transform t, float y);
void add_transformZ(Transform t, float z);

#endif