#include "meshloader.h"
#include <map>

MeshLoader::MeshLoader(){}

MeshLoader::MeshLoader(const std::string& f){
    //define a file f (our mesh file) and load it.
    loadFile(f);
}

MeshLoader::~MeshLoader(){
    clear();
}

void MeshLoader::loadFile(const std::string& file) {
    //load a series of vertices and indices into our vectors from the provided .obj files
    //this is the 3d version of this function. its almost identical but has one more variable in vertices
    clear();
    std::ifstream filestream(file);
    std::stringstream ss;
    std::string line = "";
    std::string prefix = "";
    GLint temp_glint = 0;
    float x, y, z;
    std::vector<QVector3D> vertex_position;
    std::vector<QVector2D> vertex_texcoord;
    std::vector<QVector3D> vertex_normal;

    std::vector<GLint> vertex_pos_indicies;
    std::vector<GLint> vertex_texcoord_indicies;
    std::vector<GLint> vertex_normal_indicies;

    if(!filestream.is_open()){
        throw "ERROR -> failed to open obj file.";
    }

    while (std::getline(filestream, line)) {
        ss.clear();
        ss.str(line);
        ss >> prefix;
        if (prefix == "v"){
            //vertex coordinates
            ss >> x >> y >> z;
            vertex_position.push_back(QVector3D(x,y,z));
        }
        else if(prefix == "vt"){
            //texture coordinates
            ss >> x >> y >> z;
            vertex_texcoord.push_back(QVector2D(x,y));
        }
        else if(prefix == "vn"){
            //normal coordinates
            ss >> x >> y >> z;
            vertex_normal.push_back(QVector3D(x,y,z));
        }
        else if(prefix == "f"){
            int counter = 0;
            while (ss >> temp_glint){
                //Pushing indices into correct arrays
                if (counter == 0)
                    vertex_pos_indicies.push_back(temp_glint);
                else if (counter == 1)
                    vertex_texcoord_indicies.push_back(temp_glint);
                else if (counter == 2)
                    vertex_normal_indicies.push_back(temp_glint);

                //Handling characters
                while(ss.peek() == '/'){
                    ss.ignore(1, '/');
                }
                while(ss.peek() == ' '){
                    ss.ignore(1, ' ');
                }
                ++counter;
                //Reset the counter
                if (counter > 2)
                    counter = 0;
            }
        }
    }
    vertices.resize(vertex_pos_indicies.size(), Vertex());
    for (GLuint i = 0; i < vertices.size(); ++i){
        vertices[i].position = vertex_position[vertex_pos_indicies[i] - 1];
        vertices[i].texture = vertex_texcoord[vertex_texcoord_indicies[i] - 1];
        vertices[i].normal = vertex_normal[vertex_normal_indicies[i] - 1];
        vertices[i].color = QVector3D(1.0f, 1.0f, 1.0f);
        indices.push_back(i);
    }
    filestream.close();
}

void MeshLoader::clear(){
    //clean our vertex vector for later use with a new mesh.
    this->vertices.clear();
}

void* MeshLoader::getVertices(){
    return vertices.data();
}

void* MeshLoader::getIndices(){
    return indices.data();
}

size_t MeshLoader::getVertexSize() const{
    return this->vertices.size();
}

size_t MeshLoader::getIndexSize() const{
    return this->indices.size();
}

QVector3D MeshLoader::getFirstPosition(){
    return vertices.front().position;
}


