#include <iostream>
#include "Window.h"

sf::RectangleShape Window::setRectangle(sf::Vector2f s,float x, float y, float o_x, float o_y, sf::Color color){
    sf::RectangleShape rect;
    rect.setSize(s);
    rect.setPosition(x, y);
    rect.setOrigin(o_x,o_y);
    rect.setFillColor(color);
    return rect;
}

void Window::printText(string txt, bool u, float x, float y, sf::RenderWindow *window, int f_size, bool w, bool bold){
    sf::Font font;
    if (!font.loadFromFile("../TicketMistress/src/client/font.ttf")){
        throw("Font broke");
    }

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(f_size);
    text.setStyle(sf::Text::Regular);
    text.setString(txt);

    if (w){
        text.setFillColor(sf::Color::Black);
    }
    else{
        text.setFillColor(sf::Color::Black);
    }

    if (u)
        text.setStyle(sf::Text::Underlined);

    if (bold)
        text.setStyle(sf::Text::Bold);

    if (bold && u)
        text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    sf::FloatRect tR = text.getLocalBounds();
    text.setOrigin(tR.width/2.0f,tR.height/2.0f);
    text.setPosition(x, y);
    window->draw(text);
}


Window::Window() {

}

std::vector<string> Window::start(BongoTree& btree){

    std::vector<std::pair<State, std::string>> statesList = {
    {NOWHERE, ""}, {AL, "Alabama"}, {AK, "Alaska"}, {AZ, "Arizona"}, {AR, "Arkansas"}, {CA, "California"}, {CO, "Colorado"}, {CT, "Connecticut"}, {DE, "Delaware"},
    {FL, "Florida"}, {GA, "Georgia"}, {HI, "Hawaii"}, {ID, "Idaho"}, {IL, "Illinois"}, {IN, "Indiana"}, {IA, "Iowa"}, {KS, "Kansas"}, {KY, "Kentucky"},
    {LA, "Louisiana"}, {ME, "Maine"}, {MD, "Maryland"}, {MA, "Massachusetts"}, {MI, "Michigan"}, {MN, "Minnesota"}, {MS, "Mississippi"}, {MO, "Missouri"},
    {MT, "Montana"}, {NE, "Nebraska"}, {NV, "Nevada"}, {NH, "New Hampshire"}, {NJ, "New Jersey"}, {NM, "New Mexico"}, {NY, "New York"},
    {NC, "North Carolina"}, {ND, "North Dakota"}, {OH, "Ohio"}, {OK, "Oklahoma"}, {OR, "Oregon"}, {PA, "Pennsylvania"}, {RI, "Rhode Island"},
    {SC, "South Carolina"}, {SD, "South Dakota"}, {TN, "Tennessee"}, {TX, "Texas"}, {UT, "Utah"}, {VT, "Vermont"}, {VA, "Virginia"}, {WA, "Washington"},
    {WV, "West Virginia"}, {WI, "Wisconsin"}, {WY, "Wyoming"}
    };


    std::vector<std::pair<Make,std::string>> makesList = {
        {ACURA,"Acura"}, {ALPINA,"Alpina"}, {ALFAROM,"Alfa Romero"}, {AUDI,"Audi"}, {BENZ,"Mercedes-Benz"}, {BMW,"BMW"}, {BUICK,"BUICK"}, {CHEVY,"Chevrolet"}, {FORD,"Ford"}, {GMC,"GMC"},
        {HONDA,"Honda"}, {HYUND,"Hyundai"}, {NISSAN,"Nissan"}, {RAM,"RAM"}, {SUBARU,"Subaru"}, {TESLA,"Tesla"}, {TOYOTA,"Toyota"}, {VOLKS,"Volkswagon"}, {CHRYS,"Chrystler"}, {DODGE,"Dodge"},
        {FIAT,"Fiat"}, {GM,"General Motors"}, {ISUZU,"Isuzu"}, {CADDIE,"Cadilac"}, {INTERNATL,"International"}, {JAG,"JAGUAR"}, {KWORTH,"Kenworth"}, {LAMBO,"Lambourghini"}, {LEXUS,"Lexus"}, {LINCOLN,"Lincoln"},
        {ROVER,"Rover"}, {MACK,"Mack"}, {MASR,"Maserati"}, {MERC,"Mercury"}, {MINI,"Mini"}, {MITSU,"Mitsubishi"}, {PORSCE,"Porsce"}, {PONTIAC,"Pontiac"}, {SATURN,"Saturn"}, {SMART,"Smart"},
        {SUZUKU,"Suzuku"}, {UD,"UD"}, {VOLVO,"Volvo"}, {WORKHORS,"Workhorse"}, {JEEP,"Jeep"}, {KIA,"Kia"}, {MAZDA,"Mazda"}, {VEHICLE,""}
    };

    std::vector<std::pair<Model,std::string>> modelsList = {
        {MOTORCYCLE,"Motorcycle"},
        {SPORT,"Sports Car"},
        {SUBN,"Suburban"},
        {SEDAN4D,"Four Door Sedan"},
        {SUV,"Sports Utility Vehicle"},
        {ELECTRIC,"Electric"},
        {MINIVAN,"Minivan"},
        {PICKUP,"Pickup Truck"},
        {BUS,"Bus"},
        {DUMP,"Dump Truck"},
        {FLATBED,"Flatbed Truck"},
        {MOPED,"Moped"},
        {SEDAN2D,"Two Door Sedan"},
        {TAXI,"Taxi"},
        {TRACTOR,"Tractor"},
        {TRAILER,"Trailer"},
        {UTILITY,"Utility Vehicle"},
        {VAN,"Van"},
        {SEMI,"Semi Truck"},
        {FWD,"Four-Wheel Drive"},
        {TWD,"Two-Wheel Drive"},
        {CONV,"Convertable"},
        {DIM3,"Three Dimensional Object"},
    };

    std::vector<std::pair<Color,std::string>> colorsList = {
        {RED,"Red"},
        {ORANGE,"Orange"},
        {YELLOW,"Yellow"},
        {GREEN,"Green"},
        {BLUE,"Blue"},
        {PURPLE,"Purple"},
        {BLACK,"Black"},
        {GREY,"Grey"},
        {UNKNOWN,""},
        {BROWN,"Brown"},
        {GOLD,"Gold"},
        {WHITE,"White"},
        {LIGHT,"Light-colored"},
        {NAVY,"Navy"},
        {PINK,"Pink"},
        {REDORANGE,"Red-Orange"},
        {SILVER,"Silver"},
        {TAN,"Tan"},
    };

    int curr = 0;
    int listIndex = 0;
    string name = "";
    string make = "";
    string model = "";
    string color = "";
    string year = "";
    vector<string> infoVec = {name, make, model, color, year};
    int infoType = -1;
    int width = 25;
    int height = 16;
    bool selected = false;
    bool stateSelection = false;
    bool makeSelection = false;
    bool modelSelection = false;
    bool colorSelection = false;
    bool yearSelection = false;
    bool state_not_varied = false;
    bool make_not_varied = false;
    bool model_not_varied = false;
    bool color_not_varied = false;
    bool year_not_varied = false;
    sf::RenderWindow window(sf::VideoMode(32*width, 32*height+100), "Ticket Mistress", sf::Style::Close);
    window.setFramerateLimit(60);
    sf::RectangleShape bkgd = setRectangle(sf::Vector2f(800,600),0,0,0,0, sf::Color::White);

    sf::RectangleShape StateBox;//= sf::Rect(400, 350, 100, 50);
    StateBox.setPosition(200, 210-100);
    StateBox.setSize(sf::Vector2f(400,50));
    //StateBox.setFillColor(sf::Color::Black);
    StateBox.setOutlineColor(sf::Color::Black);
    StateBox.setOutlineThickness(10);

    sf::RectangleShape MakeBox;//= sf::Rect(400, 350, 100, 50);
    MakeBox.setPosition(200, 285-100);
    MakeBox.setSize(sf::Vector2f(400,50));
    //MakeBox.setFillColor(sf::Color::Black);
    MakeBox.setOutlineColor(sf::Color::Black);
    MakeBox.setOutlineThickness(10);

    sf::RectangleShape ModelBox;//= sf::Rect(400, 350, 100, 50);
    ModelBox.setPosition(200, 360-100);
    ModelBox.setSize(sf::Vector2f(400,50));
    //ModelBox.setFillColor(sf::Color::Black);
    ModelBox.setOutlineColor(sf::Color::Black);
    ModelBox.setOutlineThickness(10);

    sf::RectangleShape ColorBox;//= sf::Rect(400, 350, 100, 50);
    ColorBox.setPosition(200, 435-100);
    ColorBox.setSize(sf::Vector2f(400,50));
    ColorBox.setOutlineColor(sf::Color::Black);
    ColorBox.setOutlineThickness(10);

    sf::RectangleShape YearBox;
    YearBox.setPosition(200,410);
    YearBox.setSize(sf::Vector2f (400,50));
    YearBox.setOutlineColor(sf::Color::Black);
    YearBox.setOutlineThickness(10);

    sf::RectangleShape StateCheckBox;//= sf::Rect(400, 350, 100, 50);
    StateCheckBox.setPosition(610, 210-100);
    StateCheckBox.setSize(sf::Vector2f(50,50));
    //StateCheckBox.setFillColor(sf::Color::Black);
    StateCheckBox.setOutlineColor(sf::Color::Black);
    StateCheckBox.setOutlineThickness(10);

    sf::RectangleShape MakeCheckBox;//= sf::Rect(400, 350, 100, 50);
    MakeCheckBox.setPosition(610, 285-100);
    MakeCheckBox.setSize(sf::Vector2f(50,50));
    //MakeCheckBox.setFillColor(sf::Color::Black);
    MakeCheckBox.setOutlineColor(sf::Color::Black);
    MakeCheckBox.setOutlineThickness(10);

    sf::RectangleShape ModelCheckBox;//= sf::Rect(400, 350, 100, 50);
    ModelCheckBox.setPosition(610, 360-100);
    ModelCheckBox.setSize(sf::Vector2f(50,50));
    //ModelCheckBox.setFillColor(sf::Color::Black);
    ModelCheckBox.setOutlineColor(sf::Color::Black);
    ModelCheckBox.setOutlineThickness(10);

    sf::RectangleShape ColorCheckBox;//= sf::Rect(400, 350, 100, 50);
    ColorCheckBox.setPosition(610, 435-100);
    ColorCheckBox.setSize(sf::Vector2f(50,50));
    ColorCheckBox.setOutlineColor(sf::Color::Black);
    ColorCheckBox.setOutlineThickness(10);

    sf::RectangleShape YearCheckBox;
    YearCheckBox.setPosition(610,410);
    YearCheckBox.setSize(sf::Vector2f (50,50));
    YearCheckBox.setOutlineColor(sf::Color::Black);
    YearCheckBox.setOutlineThickness(10);


    sf::RectangleShape submitBox;
    submitBox.setPosition(50,185);
    submitBox.setSize(sf::Vector2f (100,50));
    submitBox.setOutlineColor(sf::Color::Black);
    submitBox.setOutlineThickness(10);

    std::vector<sf::RectangleShape> statesBox, modelsBox, makesBox, colorsBox;
    State state_var;
    Color color_var;
    Model model_var;
    Make make_var;

    sf::Font font;
    if (!font.loadFromFile("../TicketMistress/src/client/font.ttf")){
        throw("Font broke");
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(stateSelection){
                statesBox.clear();

                for(int i = 0; i < 5; i++) {
                    sf::RectangleShape outlineBox;//= sf::Rect(400, 350, 100, 50);
                    outlineBox.setPosition(200, 260 + 50*i-100);
                    outlineBox.setSize(sf::Vector2f(400, 50));
                    outlineBox.setOutlineColor(sf::Color::Black);
                    outlineBox.setOutlineThickness(5);
                    statesBox.push_back(outlineBox);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && event.type == sf::Event::KeyPressed) {
                    if(listIndex+5 != statesList.size()) {
                        listIndex++;
                    }
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && event.type == sf::Event::KeyPressed) {
                    if(listIndex != 0) {
                        listIndex--;
                    }
                }
                auto position = sf::Mouse::getPosition(window);
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && infoType == 0) {
                    for (int i = 0; i < statesBox.size(); i++) {
                        if (statesBox[i].getGlobalBounds().contains(position.x, position.y)) {
                            name = statesList[i + listIndex].second;
                            state_var = statesList[i + listIndex].first;
                            stateSelection = false;
                            selected = false;
                            infoType = -1;
                        }
                    }
                    //listIndex = 0;
                }
            }

            if(makeSelection){
                makesBox.clear();

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && event.type == sf::Event::KeyPressed) {
                    //states list should be changed to make list

                    if(listIndex+5 != makesList.size()) {
                        listIndex++;
                    }
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && event.type == sf::Event::KeyPressed) {
                    if(listIndex != 0) {
                        listIndex--;
                    }
                }

                for(int i = 0; i < 5; i++) {
                    sf::RectangleShape outlineBox;//= sf::Rect(400, 350, 100, 50);
                    outlineBox.setPosition(200, 335 + 50*i-100);
                    outlineBox.setSize(sf::Vector2f(400, 50));
                    outlineBox.setOutlineColor(sf::Color::Black);
                    outlineBox.setOutlineThickness(5);
                    makesBox.push_back(outlineBox);

                    auto position = sf::Mouse::getPosition(window);
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && infoType == 1) {
                        //makesbox.size()
                        for (int i = 0; i < makesBox.size(); i++) {
                            //makesBox[i]
                            if (makesBox[i].getGlobalBounds().contains(position.x, position.y)) {
                                //mfake = makesBox[]
                                make = makesList[i + listIndex].second;
                                make_var = makesList[i + listIndex].first;
                                makeSelection = false;
                                selected = false;
                                infoType = -1;
                            }
                        }
                        //listIndex = 0;
                    }
                }
            }

            if(modelSelection){
                modelsBox.clear();
                for(int i = 0; i < 5; i++) {
                    sf::RectangleShape outlineBox;//= sf::Rect(400, 350, 100, 50);
                    outlineBox.setPosition(200, 415 + 50*i-100);
                    outlineBox.setSize(sf::Vector2f(400, 50));
                    outlineBox.setOutlineColor(sf::Color::Black);
                    outlineBox.setOutlineThickness(5);
                    modelsBox.push_back(outlineBox);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && event.type == sf::Event::KeyPressed) {
                    //states list should be changed to model list

                    if(listIndex+5 != modelsList.size()) {
                        listIndex++;
                    }
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && event.type == sf::Event::KeyPressed) {
                    if(listIndex != 0) {
                        listIndex--;
                    }
                }
                auto position = sf::Mouse::getPosition(window);
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && infoType == 2) {
                    //modelsbox.size()
                    for (int i = 0; i < modelsBox.size(); i++) {
                        //modelsBox[i]
                        if (modelsBox[i].getGlobalBounds().contains(position.x, position.y)) {
                            //mfake = modelsBox[]
//                            std::cout << listIndex << std::endl;
                            model = modelsList[i + listIndex].second;
                            model_var = modelsList[i + listIndex].first;
                            modelSelection = false;
                            selected = false;
                            infoType = -1;
                        }
                    }
                    //listIndex = 0;
                }
            }

            if(colorSelection){
                colorsBox.clear();
                for(int i = 0; i < 4; i++) {
                    sf::RectangleShape outlineBox;//= sf::Rect(400, 350, 100, 50);
                    outlineBox.setPosition(200, 495 + 50*i-100);
                    outlineBox.setSize(sf::Vector2f(400, 50));
                    outlineBox.setOutlineColor(sf::Color::Black);
                    outlineBox.setOutlineThickness(5);
                    colorsBox.push_back(outlineBox);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && event.type == sf::Event::KeyPressed) {
                    //states list should be changed to model list

                    if(listIndex+4 != colorsList.size()) {
                        listIndex++;
                    }
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && event.type == sf::Event::KeyPressed) {
                    if(listIndex != 0) {
                        listIndex--;
                    }
                }
                auto position = sf::Mouse::getPosition(window);
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && infoType == 3) {
                    //colorsbox.size()
                    for (int i = 0; i < colorsBox.size(); i++) {
                        if (colorsBox[i].getGlobalBounds().contains(position.x, position.y)) {
                            //mfake = modelsBox[]
//                            std::cout << listIndex << std::endl;
                            color = colorsList[i + listIndex].second;
                            color_var = colorsList[i + listIndex].first;
                            colorSelection = false;
                            selected = false;
                            infoType = -1;
                        }
                    }
                    //listIndex = 0;
                }
            }

            if(yearSelection){
                if(event.type == sf::Event::KeyPressed){
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && event.type == sf::Event::KeyPressed && year.size() >= 0){
                        year = year.substr(0, year.size()-1);
                    }
                    if (event.key.code >= sf::Keyboard::Num0 && event.key.code <= sf::Keyboard::Num9 && year.size() < 4){
                        int num  = event.key.code - sf::Keyboard::Num0;
                        year += to_string(num);
                    }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
                        if(std::stoi(year) < 1950 || std::stoi(year) > 2023){
                            year = "";
                        }
                        else if(std::stoi(year) > 1930 && std::stoi(year) < 2024){
                            selected = false;
                            yearSelection = false;
                            infoType = -1;
                        }


                    }
                }

            }

            if (event.type == sf::Event::Closed) {
                window.close();
                vector<string> emptyVec;
                return emptyVec;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
                vector<string> emptyVec;
                return emptyVec;
            }

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){

                auto position = sf::Mouse::getPosition(window);
                listIndex = 0;
                if(submitBox.getGlobalBounds().contains(position.x,position.y)){
                    infoVec[0] = name;
                    infoVec[1] = make;
                    infoVec[2] = model;
                    infoVec[3] = color;
                    infoVec[4] = year;
                    try {
                        Ticket temp = Ticket(state_var,make_var,color_var,model_var,std::stoi(year));
                        int blanks = 0;
                        for(auto item : infoVec){
                            if(item == ""){
                                blanks ++;
                            }

                        }
                        if(blanks > 0){

                        }
                        else{
                            unsigned char indep_vars = (state_not_varied << 4) | (make_not_varied << 3) | (model_not_varied << 2 ) | (color_not_varied << 1) | year_not_varied;
                            SecondScreen(temp, window, btree, indep_vars);
                        }
                    } catch (std::invalid_argument) {

                    }

                }
                if(StateBox.getGlobalBounds().contains(position.x, position.y)){
                    infoType = 0;
                    stateSelection = true;
                    makeSelection = false;
                    modelSelection = false;
                    colorSelection = false;
                    yearSelection = false;
                }
                else if(MakeBox.getGlobalBounds().contains(position.x, position.y)){
                    infoType = 1;
                    stateSelection = false;
                    makeSelection = true;
                    modelSelection = false;
                    colorSelection = false;
                    yearSelection = false;
                }
                else if(ModelBox.getGlobalBounds().contains(position.x, position.y)){
                    infoType = 2;
                    stateSelection = false;
                    makeSelection = false;
                    modelSelection = true;
                    colorSelection = false;
                    yearSelection = false;
                }
                else if(ColorBox.getGlobalBounds().contains(position.x, position.y)){
                    infoType = 3;
                    stateSelection = false;
                    makeSelection = false;
                    modelSelection = false;
                    colorSelection = true;
                    yearSelection = false;
                }
                else if(YearBox.getGlobalBounds().contains(position.x,position.y)){
                    infoType = 4;
                    stateSelection = false;
                    makeSelection = false;
                    modelSelection = false;
                    colorSelection = false;
                    yearSelection = true;
                } else if(StateCheckBox.getGlobalBounds().contains(position.x, position.y)){
                    state_not_varied = !state_not_varied;
                }
                else if(MakeCheckBox.getGlobalBounds().contains(position.x, position.y)){
                    make_not_varied = !make_not_varied;
                }
                else if(ModelCheckBox.getGlobalBounds().contains(position.x, position.y)){
                    model_not_varied = !model_not_varied;
                }
                else if(ColorCheckBox.getGlobalBounds().contains(position.x, position.y)){
                    color_not_varied = !color_not_varied;
                }
                else if(YearCheckBox.getGlobalBounds().contains(position.x,position.y)){
                    year_not_varied = !color_not_varied;
                }
                else{
                    infoType = -1;
                    stateSelection = false;
                    makeSelection = false;
                    modelSelection = false;
                    colorSelection = false;
                    yearSelection = false;
                }

                // in any of the text rectangles
                //listIndex = 0;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && event.type == sf::Event::KeyPressed) {
                infoVec[0] = name;
                infoVec[1] = make;
                infoVec[2] = model;
                infoVec[3] = color;
                infoVec[4] = year;
                try {
                        Ticket temp = Ticket(state_var,make_var,color_var,model_var,std::stoi(year));
                        int blanks = 0;
                        for(auto item : infoVec){
                            if(item == ""){
                                blanks ++;
                            }

                        }
                        if(blanks > 0){

                        }
                        else{
                            unsigned char indep_vars = (state_not_varied << 4) | (make_not_varied << 3) | (model_not_varied << 2 ) | (color_not_varied << 1) | year_not_varied;
                            SecondScreen(temp, window, btree, indep_vars);
                        }
                    } catch (std::invalid_argument) {

                    }
            }
        }

        window.clear(sf::Color::White);
        window.draw(bkgd);
        window.draw(StateBox);
        window.draw(MakeBox);
        window.draw(ModelBox);
        window.draw(ColorBox);
        window.draw(YearBox);
        window.draw(StateCheckBox);
        window.draw(MakeCheckBox);
        window.draw(ModelCheckBox);
        window.draw(ColorCheckBox);
        window.draw(YearCheckBox);
        window.draw(submitBox);

        printText("Welcome To Ticket Mistress!", true, width*16, 16 * height + -100-100, &window, 24, true, true);
        printText("Submit", true, 100, 205,& window, 18, true, true);
        if(infoType == 0){
            printText("Your State: " + name +"|", false, width*16, 16 * height + 50 -75-100, &window, 18, true, true);
        }else{
            printText("Your State: " + name, false, width*16, 16 * height + 50 -75-100, &window, 18, true, true);
        }

        if(infoType == 1){
            printText("Your Car Make: "+make+"|", false, width*16, 16 * height + 50-100 , &window, 18, false, true);
        }else{
            printText("Your Car Make: "+make, false, width*16, 16 * height + 50-100 , &window, 18, false, true);
        }

        if(infoType == 2){
            printText("Your Car Model: "+model+"|", false, width*16, 16 * height + 50 +75-100 , &window, 18, false, true);
        }else{
            printText("Your Car Model: "+model, false, width*16, 16 * height + 50 +75-100 , &window, 18, false, true);
        };

        if(infoType == 3){
            printText("Your Car Color: "+color+"|", false, width*16, 16 * height + 100 , &window, 18, false, true);
        }else{
            printText("Your Car Color: "+color, false, width*16, 16 * height + 100 , &window, 18, false, true);
        };

        if(infoType == 4){
            printText("Your Car Year: "+year+"|", false, width*16, 16 * height + 175 , &window, 18, false, true);
//            printText(year, false, 400, 430, &window, 18, true, true);
        }else{
            printText("Your Car Year: "+year, false, width*16, 16 * height + 175 , &window, 18, false, true);
        };


        if( state_not_varied) {
            printText("X", false, 635, 135, &window, 25, false, true);
        }
        if( make_not_varied) {
            printText("X", false, 635, 210, &window, 25, false, true);
        }
        if( model_not_varied) {
            printText("X", false, 635, 285, &window, 25, false, true);
        }
        if( color_not_varied) {
            printText("X", false, 635, 360, &window, 25, false, true);
        }
        if( year_not_varied) {
            printText("X", false, 635, 435,  &window, 25, false, true);
        }

        if(!selected && infoType == 0){
            for(auto nextState : statesBox){
                window.draw(nextState);
            }
            for(int i = 0; i < 5; i++){
                printText(statesList[i + listIndex].second, false, 400, 50 * i + 280-100, &window, 18, true, true);
            }
        }
        if(!selected && infoType == 1){
            for(auto nextMake : makesBox){
                window.draw(nextMake);
            }
            for (int i = 0; i < 5; i++) {
                //edit for make location
                //states list changed to make list
                printText(makesList[i + listIndex].second, false, 400, 50 * i + 350-100, &window, 18, true, true);
            }
        }
        //working on this one
        if(!selected && infoType == 2){
            for(auto nextModel : modelsBox){
                window.draw(nextModel);
            }
            for (int i = 0; i < 5; i++) {
                //edit for make location
                //states list changed to model list
                printText(modelsList[i + listIndex].second, false, 400, 50 * i + 430-100, &window, 18, true, true);
            }
        }

        if(!selected && infoType == 3){
            for(auto nextColor : colorsBox){
                window.draw(nextColor);
            }
            for (int i = 0; i < 4; i++) {
                //edit for make location
                //states list changed to model list
                printText(colorsList[i + listIndex].second, false, 400, 50 * i + 510-100, &window, 18, true, true);
            }
        }


        window.display();
    }
    infoVec[0] = name;
    infoVec[1] = make;
    infoVec[2] = model;
    infoVec[3] = color;
    infoVec[4] = year;
    return infoVec;
}


void Window::SecondScreen(Ticket input_match, sf::RenderWindow& window, BongoTree& btree, unsigned char indep_vars) {
    vector<vector<string>> data;
    data = {{"florida", "toyota", "four door", "blue", "2007"},{"florida", "toyota", "four door", "blue", "2007"},{"florida", "toyota", "four door", "blue", "2007"},{"florida", "toyota", "four door", "blue", "2007"},{"florida", "toyota", "four door", "blue", "2007"},{"florida", "toyota", "four door", "blue", "2007"},{"florida", "toyota", "four door", "blue", "2007"},{"florida", "toyota", "four door", "blue", "2007"}};
    int curr = 0;
    std::pair<float,std::set<Ticket*>> result = btree.query(input_match, indep_vars);
    string prob = to_string(result.first);
    int scrollVal = 0;
    sf::RectangleShape Box;//= sf::Rect(400, 350, 100, 50);
    Box.setPosition(20, 40);
    Box.setSize(sf::Vector2f(50, 50));
    Box.setOutlineColor(sf::Color::Black);
    Box.setOutlineThickness(5);
    sf::RectangleShape ResultBox;//= sf::Rect(400, 350, 100, 50);
    ResultBox.setPosition(330, 415);
    ResultBox.setSize(sf::Vector2f(150, 50));
    ResultBox.setOutlineColor(sf::Color::Black);
    ResultBox.setOutlineThickness(5);

    while(window.isOpen()){
        window.clear(sf::Color::White);
        sf::Event event;
        int max = 5;
        if(data.size() < max){
            max = data.size();
        }
        for(int i = 0; i < max; i++) {
            sf::RectangleShape outlineBox;//= sf::Rect(400, 350, 100, 50);
            outlineBox.setPosition(100, 40 + 70*i);
            outlineBox.setSize(sf::Vector2f(600, 50));
            outlineBox.setOutlineColor(sf::Color::Black);
            outlineBox.setOutlineThickness(5);
            if(i == curr){
                outlineBox.setOutlineThickness(10);
            }
            window.draw(outlineBox);

            string infoString1 = "";
            string infoString2 = "";
            for(int j = 0; j < data[scrollVal+i].size(); j++){
                if(j == 0){
                    infoString1 += "State: ";
                    infoString1 += data[scrollVal+i][j];
                    infoString1 += "\t";
                }
                else if(j == 1){
                    infoString1 += "Make: ";
                    infoString1 += data[scrollVal+i][j];
//                    infoString1 += "\t";
                }
                else if(j == 2){
                    infoString2 += "Model: ";
                    infoString2 += data[scrollVal+i][j];
                    infoString2 += "\t";
                }
                else if(j == 3){
                    infoString2 += "Color: ";
                    infoString2 += data[scrollVal+i][j];
                    infoString2 += "\t";
                }
//                else if(j == 4){
//                    infoString2 += "Time: ";
//                    infoString2 += data[scrollVal+i][j];
//                    infoString2 += "\t";
//                }
                else if(j == 4){
                    infoString2 += "Year: ";
                    infoString2 += data[scrollVal+i][j];
                }
                else{
                    std::cout << "Error" << "\n";
                }

            }
            printText(infoString1, false, 400, 55+ i*70 , &window, 18, false, true);
            printText(infoString2, false, 400, 75+ i*70 , &window, 18, false, true);
        }


        //text
        printText(to_string(1+curr + scrollVal)+"/" + to_string(data.size()), false, 400, 75+ max*70 -30 , &window, 18, false, true);

        while(window.pollEvent(event)){
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                auto position = sf::Mouse::getPosition(window);
                if(Box.getGlobalBounds().contains(position.x, position.y)){
                    return;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && event.type == sf::Event::KeyPressed) {
                if(curr <4) {
                    curr++;
                }else{
                    if(scrollVal + 2 != max){
                        scrollVal++;
                    }
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && event.type == sf::Event::KeyPressed) {
                if(curr > 0) {
                    curr--;
                }else{
                    if(scrollVal != 0){
                        scrollVal--;
                    }
                }

            }
        }
        window.draw(Box);
        window.draw(ResultBox);
        printText("Back", true, 44, 50, &window, 18, false, true);
        printText(prob, true, 398, 430, &window, 18, false, true);
        window.display();
    }

};


