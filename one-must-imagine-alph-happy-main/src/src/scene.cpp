#include "scene.h" // Inclusion du fichier d'en-tête "scene.h"

// Définition du constructeur de la classe Scene
Scene::Scene() : AppCamera(1920, 1080) {
     // Initialisation de la classe mère avec la taille de la fenêtre
}

// Méthode d'initialisation de la scène
int Scene::init() {
    // Initialisation des ressources de la scène, comme les meshes et les textures
    
    // Chargement des meshes depuis des fichiers
    m_grid = read_mesh("asset/floor3.obj");
    m_alph = read_mesh("asset/PionRaph.obj");
    m_monstre = read_mesh("asset/PionMonstre.obj");
    m_death = read_mesh("asset/TombStone.obj");
    
    w_point = WidgetPoint();

    // Création de textures à partir de fichiers
    m_texture1= read_texture(0, "asset/vert.png");
    m_texture2= read_texture(0, "asset/violet.png");
    m_texture3= read_texture(0, "asset/bleu.png");
    m_texture4= read_texture(0, "asset/bleu_fonce.png");
    m_belze= read_texture(0, "asset/belze.png");
    m_ogrest= read_texture(0, "asset/ogrest.png");

    // Création du programme shader
    m_program= read_program("src/tuto9_textures.glsl");
    program_print_errors(m_program);

    // Création d'éléments d'interface utilisateur
    i_health = create_ImageViewer("asset/health.png");
    i_turnLeft = create_ImageViewer("asset/fleche2.png");
    i_turnRight = create_ImageViewer("asset/fleche.png");
    i_passed = create_ImageViewer("asset/passed.png");
    i_HUD = create_ImageViewer("asset/hud_omiah.png");
    i_background = create_ImageViewer("asset/background.png");
    i_firework = create_ImageViewer("asset/feu-dartifice.png");
    i_portrait = create_ImageViewer("asset/portrait.png");
    i_health_m = create_ImageViewer("asset/health_m.png");
    i_xp_bar = create_ImageViewer("asset/xp_bar.png");
    i_play = create_ImageViewer("asset/play.png");
    i_accueil = create_ImageViewer("asset/accueil.png");

    t_pa = create_widgets();
    t_pm = create_widgets();

    // Configuration OpenGL
    glClearColor(0.5f, 0.5f, 0.5f, 1.f);
    glClearDepth(1.f);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);

    // Initialisation de la grille de jeu
    int width = game.level.grid.size();
    int height = game.level.grid[0].size();
    if (width == 0 || height == 0) {
        // Gérer le cas où la grille est vide
        return 0;
    }
    // Initialisation des position de grille + inclusion des triangles pour les ray
    Init_Triangle_grid(width, height);

    // Configuration de la caméra de l'application
    Point pmin, pmax;
    pmin = Point(0, 0.f, 0);
    pmax = Point(width / 4 , 3.f, height / 4  - 2.);
    camera().lookat(pmax, pmin); // Paramétrage de la position de la caméra

    

    return 0; // Succès de l'initialisation
}

// Méthode de libération des ressources de la scène
int Scene::quit() {
    // Libération du programme shader
    release_program(m_program);
    
    // Libération texture
    glDeleteTextures(1, &m_texture1);
    glDeleteTextures(1, &m_texture2);
    glDeleteTextures(1, &m_texture3);
    glDeleteTextures(1, &m_texture4);
    glDeleteTextures(1, &m_ogrest);
    glDeleteTextures(1, &m_belze);

    // Libération image
    release_ImageViewer(i_health);
    release_ImageViewer(i_HUD);
    release_ImageViewer(i_turnLeft);
    release_ImageViewer(i_turnRight);
    release_ImageViewer(i_passed);
    release_ImageViewer(i_background);
    release_ImageViewer(i_firework);
    release_ImageViewer(i_portrait);
    release_ImageViewer(i_health_m);
    release_ImageViewer(i_xp_bar);
    release_ImageViewer(i_accueil);
    release_ImageViewer(i_play);

    // Libération widget
    release_widgets(t_pa);
    release_widgets(t_pm);

    // Libération widget point
    w_point.Release_Widget();


    // Libération des meshes
    m_alph.release();
    m_monstre.release();
    m_grid.release();
    m_death.release();
    return 0; // Succès de la libération des ressources
}

// Méthode de mise à jour de la scène
int Scene::update( const float time, const float delta ){

    static float elapsedTime = 0.0f; // Temps écoulé depuis la dernière mise à jour
    float deltaTime = 0.05f;
    // Ajouter le delta actuel à elapsedTime
    elapsedTime += deltaTime;
    
    // Mettre à jour la scène si suffisamment de temps s'est écoulé
    if (elapsedTime >= time) {
        // Mettre à jour la grille de jeu et d'autres éléments
        //game.level.displayGrid();
        

       if(game.win ){
            level ++;
            quit();
            game.Changement_Map(game.level );
            if(game.monterLvl){
                w_point.setPoint(game.point);
                game.point = 0;
                distribAttributePoint = true;
                
            } 
            init();
            initCamera = true;
            game.win = false;
        }
        game.updateGrid();
        elapsedTime = 0; // Réinitialiser le temps écoulé
    }
    
    // Retourner une valeur pour indiquer le statut de la mise à jour
    return 0; // Par exemple, 0 pour indiquer que la mise à jour s'est bien déroulée
}

// Méthode de rendu de la scène
int Scene::render() {
    // Effacement du tampon de couleur et du tampon de profondeur
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Rendu de la scène, y compris les éléments d'interface utilisateur

    int mx, my;
    unsigned int mb= SDL_GetRelativeMouseState(&mx, &my);
    int mousex, mousey;
    SDL_GetMouseState(&mousex, &mousey);

    if(!play){
        draw_background(i_accueil, window_width(), window_height());

        b_play.initButton(i_play, window_width()/2 - i_play.width/2 * 0.90 , window_height()/8 * 7.6 , 1., 1.);
        draw_button(b_play,  window_width(), window_height());
        b_play.interacted(play, mousex, mousey, mb);
    }
    else {
        // Récupération des dimensions de la grille de jeu
        int width = game.level.grid.size();
        int height = game.level.grid[0].size();
        if (width == 0 || height == 0) {
            return 0;
        }

        init_button_scene();

        // Utilisation du programme shader
        glUseProgram(m_program);

        draw_background(i_background, window_width(), window_height());

        initPosCamera(m_camera, 0, 45);

        // Dessin de la grille de jeu
        draw_grid(width, height);

        // Mise à jour des entités (joueur et monstres)
        Update_Player(width, height);
        Monster_Update(width, height);
        update( 2.f, delta_time() ); // Mise à jour de la scène
        
        draw_element2d_scene(mb, mousex, mousey);

        interactedButtonScene();

        if(distribAttributePoint) w_point.PointSplit(window_width(), window_height(), mousex, mousey, mb, distribAttributePoint, game.alph);

    }
    

    return 1; // Succès du rendu
}

Point Scene::interpolate(Point a, Point b, float t) {
    // Calcule la position interpolée entre deux points selon un paramètre t
    Point p;
    p.x = (1 - t) * a.x + t * b.x;
    p.y = (1 - t) * a.y + t * b.y;
    p.z = -0.1;
    return p;
}

// Méthode pour calculer l'angle de rotation entre deux points
float Scene::calculateRotationAngle(Point posActuelle, Point posCible) {
 
    float dx = posActuelle.x - posCible.x;
    float dy = posActuelle.z - posCible.z;

    float angle_rad = atan2(dx, dy);

    float angle_deg = angle_rad * 180.0 / M_PI;

    if (angle_deg < 0) {
        angle_deg += 360.0;
    }

    return angle_deg ;
}
// Méthode pour initialiser la position de la caméra
Orbiter Scene::initPosCamera(Orbiter& camera, int x, int y){
    if(initCamera){
        m_camera.rotation(x, y);
        initCamera = false;
    }
    return camera;
}
// Méthode pour convertir les coordonnées de l'écran en coordonnées de la scène
Point Scene::Canva_Point(Orbiter camera, Point point){
    camera.projection(window_width(), window_height(), 45);
    Transform model=Identity();
    Transform view= camera.view();
    Transform projection= camera.projection();
    Transform viewport= camera.viewport();
    Transform inv= Inverse(viewport * projection * view * model);
    return inv(point);
}
// Méthodes pour sélectionner une case pour le déplacement 
void Scene::Select_Tile_Move(float offset, int width, int height, Transform& t, GLuint m_texture)
{
        
    int movementPoints = game.alph.statActuelles.getStat(MOVEMENT_POINT);
    int mx, my;
    unsigned int mb= SDL_GetRelativeMouseState(&mx, &my);
    

    int mousex, mousey;
    SDL_GetMouseState(&mousex, &mousey);

    Transform inv;
    
    
    for(int x = 0 ; x < width; x++)
        for(int y = 0 ; y < height ; y++){
                Point extremite = Canva_Point(m_camera, Point(mousex +0.5 , mousey +0.5, 1));
                extremite.z *= -1;
                extremite.z += offset;
                Point origine = Canva_Point(m_camera,Point(mousex +0.5, mousey +0.5 , 0));
                origine.z *= -1;
                origine.z += offset ;
                Ray ray(origine, extremite);

                Hit hit;
            
            for (int i = 0; i < triangles[x][y].size(); i++)
            {
                
                float tmax = ray.tmax;

                if (Hit h = triangles[x][y][i].intersect(ray, hit.t)) 
                {
                    if (h.t > 0) 
                    {
                        hit= h;
                    }
                }
            }
            if(hit && !game.select_spell){
                for(int i = 0; i < game.monstre.size(); i++)
                if (game.level.grid[x][y] < 1 && std::vector<int> {x, y} != game.monstre[i].getPosEntity()) {
                    Transform t = Translation(tilePosition[x][y].x, 1.51, tilePosition[x][y].z);
                    
                    draw( m_grid,t, camera(), m_texture);  
                    
                    if(mb & SDL_BUTTON(1) && game.alph.manhattan_distance(game.alph.getPosEntity(), std::vector<int> {x, y}) <=  movementPoints){
                    
                    game.playerMove = std::vector<int> {x, y}; 
                    game.selectTile = true;
                    } 

                }
        
                    
            }
        }

}
// Méthodes pour sélectionner une case pour lancer un sort
void Scene::Select_Tile_Spell(float offset, int width, int height, Transform& t, GLuint m_texture)
{
        
    int movementPoints = game.alph.statActuelles.getStat(MOVEMENT_POINT);
    int mx, my;
    unsigned int mb= SDL_GetRelativeMouseState(&mx, &my);
    

    int mousex, mousey;
    SDL_GetMouseState(&mousex, &mousey);

    Transform inv;
    
    
    for(int x = 0 ; x < width; x++)
        for(int y = 0 ; y < height ; y++){
                Point extremite = Canva_Point(m_camera, Point(mousex +0.5 , mousey +0.5, 1));
                extremite.z *= -1;
                extremite.z += offset;
                Point origine = Canva_Point(m_camera,Point(mousex +0.5, mousey +0.5 , 0));
                origine.z *= -1;
                origine.z += offset ;
                Ray ray(origine, extremite);

                Hit hit;
            
            for (int i = 0; i < triangles[x][y].size(); i++)
            {
                
                float tmax = ray.tmax;

                if (Hit h = triangles[x][y][i].intersect(ray, hit.t)) 
                {
                    if (h.t > 0) 
                    {
                        hit= h;
                    }
                }
            }
            if(hit ){
                    if(game.level.grid[x][y] != '1'){
                    //std::cout << "game.select_spell" ;
                    Transform t = Translation(tilePosition[x][y].x, 1.51, tilePosition[x][y].z);
                    
                    draw( m_grid,t, camera(), m_texture);  
                    
                    if(mb & SDL_BUTTON(1)){
                        
                        for(int i; i < game.monstre.size(); i++){
                            if(std::vector<int> {x, y} == game.monstre[i].getPosEntity()){
                                game.indexMonster = i;

                                game.select_monster = true;
                            }
                            
                        }  
                    }
                }
            }
        }
}
    
// Méthode pour initialiser tte les positions des triangle de chaque mesh
void Scene::Init_Triangle_grid(int width, int height)
{
    triangles.resize(width);
    tilePosition.resize(width);
    for (int x = 0; x < width; x++) {
        triangles[x].resize(height);
        tilePosition[x].resize(height);
    }

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {

            tilePosition[x][y] = Point((static_cast<float>(x) / 4), 2., (static_cast<float>(y) / 4));

            m_grid.move_vertex(tilePosition[x][y]);
             //std::cout<< m_grid.m_positions[x].x << std::endl;  
            //std::cout<< tileMesh[x][y].m_positions[x].x << std::endl;
            int n=  m_grid.triangle_count();

            for(int i= 0; i < n; i++){

                triangles[x][y].emplace_back( m_grid.triangle(i), i);      

            }
            m_grid.move_vertex(Point(-tilePosition[x][y].x, -tilePosition[x][y].y, -tilePosition[x][y].z)); 
                     
   
        }
    }
}
// Méthode pour mettre à jour les monstres dans la scène
void Scene::Monster_Update(int width, int height)
{
    if(!distribAttributePoint){
        for(int i = 0; i < game.monstre.size(); i++){
            std::vector<int> posEntity = game.monstre[i].getPosEntity();
            int posX = posEntity[0];
            int posY = posEntity[1];
            if (posX >= 0 && posX < width && posY >= 0 && posY < height) {
                Transform t2 = Translation(tilePosition[posX][posY].x, 1.6, tilePosition[posX][posY].z) ;
                Use_Texture(t2, m_belze);
                Use_Texture(t2, m_ogrest);
                Transform rotate;
                if (game.registreMove[i].size() > 3) {
                    Point currentPos = tilePosition[game.registreMove[i][game.registreMove[i].size() - 2][0]][game.registreMove[i][game.registreMove[i].size() - 2][1]];
                    Point targetPos = tilePosition[posX][posY];
                    float rotationAngle = calculateRotationAngle(currentPos, targetPos);
                    rotate = RotationY(rotationAngle);
                }
                if(!game.monstre[i].Death()){
                    if(game.monstre[i].getName() == "belzebuth") draw(m_monstre, t2 * rotate, camera(),  m_belze);
                    if(game.monstre[i].getName() == "ogrest") draw(m_monstre, t2 * rotate, camera(),  m_ogrest);
                }
                else draw(m_death, t2 * RotationY(i * 10.) , camera(),  m_texture4);
                

            }
        }  
    }

}

void Scene::Use_Texture(Transform t, GLuint m_texture)
{
    program_uniform(m_program, "mvpMatrix", t);
    program_use_texture(m_program, "texture", 0, m_texture);
}
// Méthode pour mettre à jour le joueur dans la scène
void Scene::Update_Player(int width, int height)
{
    Transform t;
    if((!game.selectTile && !game.select_spell) && !select && !distribAttributePoint){
        
        Use_Texture(t, m_texture1);
        Select_Tile_Move(0., width, height,t, m_texture1);
    }
    //std::cout << game.select_spell ;
    if(game.select_spell && !select && !distribAttributePoint){
      // std::cout << "game.select_spell" ;

        Use_Texture(t, m_texture2);
        Select_Tile_Spell(0., width, height,t, m_texture2);
    }

    std::vector<int> alphPos = game.alph.getPosEntity();
    Transform rotate;

    if (game.registreMove[0].size() > 3) {
        Point currentPos = tilePosition[game.registreMove[0][game.registreMove[0].size() - 2][0]][game.registreMove[0][game.registreMove[0].size() - 2][1]];
        Point targetPos = tilePosition[alphPos[0]][alphPos[1]];
        float rotationAngle = calculateRotationAngle(currentPos, targetPos);
        rotate = RotationY(rotationAngle);
    } 

    Transform t1 = Translation(tilePosition[alphPos[0]][alphPos[1]].x, 1.6, tilePosition[alphPos[0]][alphPos[1]].z);
    draw(m_alph, t1 * rotate, camera());
}
// Méthodes pour dessiner des éléments d'interface utilisateur
void Scene::draw_attribute(Widgets widgets, int width, int height, const Color& color , int text)
{
    begin(widgets);
        begin_line(widgets);
        default_color(  widgets,  color );
        label(widgets, "%d", text);
    end(widgets);
    // afficher l'interface
    draw(widgets, width, height);
}
// Dessine les portraits des monstres dans l'interface utilisateur
void Scene::draw_portrait(){
    for(int i = 0; i < game.monstre.size(); ++i){
        float currentHealth = game.monstre[i].statActuelles.getStat(HEALTH);
        float health = game.monstre[i].attEntity.getStat(HEALTH);
        draw(i_portrait, window_width(),  window_height(),window_width()/8 * 7.2 ,  window_height()/8 * 1.8 + i * 100,1., 1.);
        draw(i_health_m, window_width(),  window_height(),window_width()/8 * 7.23 ,  window_height()/8 * 1.7 + i * 100,currentHealth/health, 1.);

    }
}
// Dessine la grille de jeu dans la scène
void Scene::draw_grid(int width, int height){
    for (int x = 0; x < width; x++) 
        for (int y = 0; y < height; y++) {
        
           
            if (game.level.grid[x][y] == '1') {
                Transform t = Translation(tilePosition[x][y].x, 1.6, tilePosition[x][y].z);
                Use_Texture(t, m_texture4);
                draw( m_grid,t, camera(), m_texture4);  
            }

            
            Transform t = Translation(tilePosition[x][y].x, 1.5, tilePosition[x][y].z);
            Use_Texture(t, m_texture3);
            draw( m_grid, t, camera(), m_texture3);
            
        }
    
}
// Gère l'interaction avec les boutons dans la scène
void Scene::interactedButtonScene(){


    if(click)
    {
        game.endRound = true;
        click = false;
    }

    if(turnLeft)
    {
        m_camera.rotation(-2, 0);
        turnLeft = false;
    }

    if(turnRight)
    {
        m_camera.rotation(2, 0);
        turnRight = false;
    }
   
    if(firework)
    {
        game.select_spell = !game.select_spell;
        game.spellChoise = FIREWORK;
        firework = false;
    }
}
// Dessine les éléments 2D de l'interface utilisateur dans la scène
void Scene::draw_element2d_scene(int mb, int mousex, int mousey){

    draw_button(b_endRound, window_width(), window_height());
    b_endRound.interacted(click, mousex, mousey, mb, select);

    draw_background(i_HUD, window_width(), window_height());

    draw_button(b_turnLeft, window_width(), window_height());
    b_turnLeft.interacted2(turnLeft, mousex, mousey, mb);

    draw_button(b_turnRight, window_width(), window_height());
    b_turnRight.interacted2(turnRight, mousex, mousey, mb);

    draw_button(b_firework, window_width(), window_height());
    b_firework.interacted(firework, mousex, mousey, mb);
    
    draw_attribute(t_pm, window_width()/8 *6.5, window_height()/8 * 1.2, Color( 0.1f, 0.1f, 0.1f, 1.f ) , game.alph.statActuelles.getStat(MOVEMENT_POINT));
    draw_attribute(t_pa, window_width()/8 *7, window_height()/8 * 1.1 , Color( 0.1f, 0.1f, 0.1f, 1.f ) , game.alph.statActuelles.getStat(ACTION_POINT));

    draw_attribute(t_pa, window_width()/8 * 2.15,  window_height()/8 * 7.15, Color( 0.1f, 0.1f, 0.1f, 1.f ) , game.alph.getLvl());

    float currentHealth = game.alph.statActuelles.getStat(HEALTH);
    float health = game.alph.attEntity.getStat(HEALTH);

    draw(i_health, window_width(),  window_height(),window_width()/8 *2.57,  window_height()/16 *14.81,currentHealth/health, 1.);

     float currentXp = game.alph.getXpPlayer();
    float xp = game.alph.getXpLvlPlayer();

    draw(i_xp_bar, window_width(),  window_height(),window_width()/32 * 1.89,  window_height()/8 * 5.81 ,1., currentXp/xp);
    
    draw_portrait();
}
// Initialise les boutons de l'interface utilisateur dans la scène
void Scene::init_button_scene(){
    b_endRound.initButton(i_passed, window_width()/2 - i_passed.width/2 , window_height()/2 + 250, 1., 1.);
    b_turnLeft.initButton(i_turnLeft, window_width()/2 - i_turnLeft.width - 10, 120, 1., 1.);
    b_turnRight.initButton(i_turnRight, window_width()/2 + 10, 120, 1., 1.);
    b_firework.initButton(i_firework, window_width()/8 * 6.30,  window_height()/8 * 7.40, 1., 1.);
    w_point.Init_Widget(window_width(), window_height());
}
