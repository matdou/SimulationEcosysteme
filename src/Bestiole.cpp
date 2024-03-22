#include "Bestiole.h"

#include <cmath>
#include <cstdlib>

#include "Milieu.h"
#include "Yeux.h"
#include "Oreilles.h"

const double Bestiole::AFF_SIZE = 8.;
const double Bestiole::MAX_VITESSE = 15.;
const double Bestiole::LIMITE_VUE = 30.;
const double Bestiole::COLLISION_DISTANCE = 10.;
const double Bestiole::EXPLOSION_PROBABILITY = 0.01; //TODO

int Bestiole::next = 0;

Bestiole::Bestiole(void) {
    identite = ++next;

    x = y = 0;
    cumulX = cumulY = 0.;
    orientation = static_cast<double>(rand()) / RAND_MAX * 2. * M_PI;
    vitesse = static_cast<double>(rand()) / RAND_MAX * MAX_VITESSE;

    couleur = {
        {static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 230.),
         static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 230.),
         static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 230.)}};

    std::cout << "Bestiole : created from default, with identite : " << identite
              << std::endl;

    lifeTime = -1;  // -1 means infinite life
    vitesseInitiale = vitesse;
}


Bestiole::Bestiole(const Bestiole &b) {
    identite = ++next;
    x = b.x;
    y = b.y;
    cumulX = cumulY = 0.;
    orientation = b.orientation;
    vitesse = b.vitesse;
    vitesseInitiale = b.vitesseInitiale;
    couleur = b.couleur;
    lifeTime = b.lifeTime;
    std::cout << "Bestiole : created from copy constructor, with identite : "
              << identite << std::endl;
}


Bestiole::~Bestiole(void) {
    std::cout << "dest Bestiole (" << identite << ")" << std::endl;
    // delete[] couleur;
}



// getters and setters
int Bestiole::getIdentite() const { return identite; }

void Bestiole::setVitesse(double nouvelle_vitesse) {
    vitesse = std::min(std::max(0.0, nouvelle_vitesse), MAX_VITESSE);
}
double Bestiole::getVitesse() const { return vitesse; }

void Bestiole::setOrientation(double nouvelle_orientation) {
    orientation = nouvelle_orientation;
}

double Bestiole::getOrientation() const { return orientation; }

void Bestiole::initCoords(int xLim, int yLim) {
    x = rand() % xLim;
    y = rand() % yLim;
}

void Bestiole::bouge(int xLim, int yLim) {
    double nx, ny;
    double dx = cos(orientation) * vitesse;
    double dy = -sin(orientation) * vitesse;
    int cx, cy;

    cx = static_cast<int>(cumulX);
    cumulX -= cx;
    cy = static_cast<int>(cumulY);
    cumulY -= cy;

    nx = x + dx + cx;
    ny = y + dy + cy;

    if ((nx < 0) || (nx > xLim - 1)) {
        orientation = M_PI - orientation;
        cumulX = 0.;
    } else {
        x = static_cast<int>(nx);
        cumulX += nx - x;
    }

    if ((ny < 0) || (ny > yLim - 1)) {
        orientation = -orientation;
        cumulY = 0.;
    } else {
        y = static_cast<int>(ny);
        cumulY += ny - y;
    }
}

void Bestiole::action(Milieu &monMilieu) {
    bouge(monMilieu.getWidth(), monMilieu.getHeight());
}

void Bestiole::draw(UImg &support) {
    double xt = x + cos(orientation) * AFF_SIZE / 2.1;
    double yt = y - sin(orientation) * AFF_SIZE / 2.1;

    support.draw_ellipse(x, y, AFF_SIZE, AFF_SIZE / 5.,
                         -orientation / M_PI * 180., couleur.data());
    support.draw_circle(xt, yt, AFF_SIZE / 2., couleur.data());
}

bool operator==(const Bestiole &b1, const Bestiole &b2) {
    return (b1.identite == b2.identite);
}

// handles multiple sensors (Yeux + Oreilles)
bool Bestiole::jeTeVois(const Bestiole &b) const {
    for (const auto &capteur : capteurs) {
        if (capteur->jeTeVois(b, *this)) {
            return true;
        }
    }

    return false;
}

void Bestiole::setCouleur(int r, int g, int b) {
    couleur[0] = r;
    couleur[1] = g;
    couleur[2] = b;
}

void Bestiole::setLifeExpectancy(double lifeExpectancy) {
    this->lifeTime = lifeExpectancy;
}

double Bestiole::getLifeExpectancy() const { return lifeTime; }

void Bestiole::setLifeExpectancyFromAvg(double averageLifeExpectancy,
                                        double std) {
    if (averageLifeExpectancy < 0) {
        this->lifeTime = -1;
        return;
    }
    this->lifeTime = averageLifeExpectancy +
                     std * (static_cast<double>(rand()) / RAND_MAX - 0.5);
}


double Bestiole::getX() const {
    return x + cumulX;
}

double Bestiole::getY() const {
    return y + cumulY;
}

void Bestiole::addCapteursFromString(const std::string& s) {
    if (s == "Yeux") {
        std::unique_ptr<Capteur> capteur = std::make_unique<Yeux>();
        capteurs.push_back(std::move(capteur));

    }
    if (s == "Oreilles") {
        std::unique_ptr<Capteur> capteur = std::make_unique<Oreilles>();
        capteurs.push_back(std::move(capteur));
    }
}



double Bestiole::getVitesseInitiale() const { return vitesseInitiale; };


bool Bestiole::collidesWith(const Bestiole &other) const {
    double distance = sqrt(pow(getX() - other.getX(), 2) +
                           pow(getY() - other.getY(), 2));
    if (distance < COLLISION_DISTANCE && distance > 0.) {
        // Collision
        return true;
    }
}


void Bestiole::updateCollision() {
    if (static_cast<double>(rand()) / RAND_MAX < EXPLOSION_PROBABILITY) {
        // Explosion
        setLifeExpectancy(0);
    }
    else {
        // Change direction
        double orientation = getOrientation() + M_PI;
        if (orientation > 2 * M_PI) {
            orientation -= 2 * M_PI;
        }
        setOrientation(orientation);
    }
}

void Bestiole::setMultiplicateurVitesse(double multiplicateurVitesse) {
    this -> multiplicateurVitesse = multiplicateurVitesse;
    this -> vitesse = vitesseInitiale * multiplicateurVitesse;
    vitesse = std::min(std::max(0.0, vitesse), MAX_VITESSE);
    this -> vitesse = vitesse;
    this -> vitesseInitiale = vitesseInitiale;
}

void Bestiole::setMultiplicateurProtection(double multiplicateurProtection) {
    this->multiplicateurProtection = multiplicateurProtection;
}

void Bestiole::setMultiplicateurDiscretion(double multiplicateurDiscretion) {
    this->multiplicateurDiscretion = multiplicateurDiscretion;
}
