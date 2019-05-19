#include "init.h"
#include "random"

using namespace sf;

class texturePath{
public:
    texturePath(const std::string str, const bool a){
        path = str;
        abilityCross = a;
    }

    bool abilityCross;
    std::string path;
    Texture texture;
};

class BackgroundType{
public:
    Background background;
    Sprite picture;
};

Background background[1000][1000];
std::map <int, BackgroundType> backgroundTypes;

std::vector<texturePath> textures = {
        texturePath("pngForGame/box/boxLD.png", false),                             //1
        texturePath("pngForGame/box/boxRD.png", false),                             //
        texturePath("pngForGame/box/boxLU.png", false),                             //
        texturePath("pngForGame/box/boxRU.png", false),                             //
        texturePath("pngForGame/fense/fenseCornerLD.png", false),                   //5
        texturePath("pngForGame/fense/fenseCornerRD.png", false),                   //
        texturePath("pngForGame/fense/fenseCornerLU.png", false),                   //
        texturePath("pngForGame/fense/fenseCornerRU.png", false),                   //
        texturePath("pngForGame/fense/fenseHorisontal.png", false),                 //
        texturePath("pngForGame/fense/fenseVertical.png", false),                   //10
        texturePath("pngForGame/pavement/pavementBorderDown.png", true),            //
        texturePath("pngForGame/pavement/pavementBorderLeft.png", true),            //
        texturePath("pngForGame/pavement/pavementBorderUp.png", true),              //
        texturePath("pngForGame/pavement/pavementBorderRight.png", true),           //
        texturePath("pngForGame/pavement/pavementHorisontal.png", true),            //15
        texturePath("pngForGame/pavement/pavementVertical.png", true),              //
        texturePath("pngForGame/grassBeach.png", true),                             //
        texturePath("pngForGame/grassBeachFlower.png", true),                       //
        texturePath("pngForGame/river.png", true),                                  //
        texturePath("pngForGame/road.png", true),                                   //20
        texturePath("pngForGame/sand.png", true),                                   //
        texturePath("pngForGame/grass.png", true)                                   //
};

void setBackground(RenderWindow &window) {
    BackgroundType backgroundType;

    for(int i = 0; i < textures.size(); i++){
        Background tmp(textures.operator[](i).abilityCross);

        textures.operator[](i).texture.loadFromFile(textures.operator[](i).path);
        backgroundType.picture.setTexture(textures.operator[](i).texture);
        backgroundType.background = tmp;
        backgroundType.background.type = i;

        backgroundTypes.insert(std::pair<int, BackgroundType>(i, backgroundType));
    }

    for (int i = 0; i < sizeWindow.x; i++) {
        for (int j = 0; j < sizeWindow.y; j++)
            background[i][j] = backgroundTypes.operator[](21).background;
    }

//river Generator
    srand(time(NULL));

    int numberRivers = 2000;
    Vector2i coordinatesOfRiverSource[numberRivers];

    for (auto &i : coordinatesOfRiverSource) {
        i.x = rand() % sizeWindow.x;
        i.y = rand() % sizeWindow.y;
        background[i.x][i.y] = backgroundTypes.operator[](18).background;
    }

    for (int i = 0; i < numberRivers; i++) {
        int I = coordinatesOfRiverSource[i].x;
        int J = coordinatesOfRiverSource[i].y;

        while(1){
            int nextI = rand() % 2 - 1;
            int nextJ = rand() % 2 - 1;
            if((I+nextI >= 0) && (I + nextI < sizeWindow.x) && (J+nextJ >= 0) && (J + nextJ < sizeWindow.y)){
                if(background[I+nextI][J+nextJ].type == 21){
                    background[I+nextI][J+nextJ] = backgroundTypes.operator[](18).background;
                    background[I+nextI][J+nextJ].type = 18;
                }

                else
                    break;
            }
            else
                break;

        }
    }
}

