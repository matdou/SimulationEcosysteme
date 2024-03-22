#include "Prevoyante.h"

#include "BestioleFactory.h"
#include "Capteur.h"

static bool dummy = []()
{
    BestioleFactory::registerType(
        "Prevoyante", []() -> Bestiole *
        { return new Prevoyante(); });
    return true;
}();

Prevoyante::Prevoyante()
{
    setCouleur(255, 255, 0); // Jaune
}

Prevoyante::~Prevoyante()
{
    // Destructor
}

void Prevoyante::update(const std::vector<std::reference_wrapper<Bestiole>> &voisins)
{
    // On ne fait rien

    if (!voisins.empty())
    {
        double currentDistance;
        double dx = 0;
        double dy = 0;
        double minDistance = 1000000000;
        std::shared_ptr<Bestiole> nearestBestiole = nullptr;
        for (const auto &ptr : voisins)
        {
            Bestiole &voisin = ptr.get();
            currentDistance = std::pow(this->getX() - voisin.getX(), 2) +
                              std::pow(this->getY() - voisin.getY(), 2);
            if (currentDistance < minDistance)
            {
                dx = voisin.getX() - this->getX();
                dy = voisin.getY() - this->getY();
                minDistance = currentDistance;
            }
        }

        double alpha = M_PI / 10;
        double newOrientation;
        double phi = atan2(dy, dx);
        if (phi >= 0)
        {
            newOrientation = this->getOrientation() + alpha;
        }
        else
        {
            newOrientation = this->getOrientation() - alpha;
        }
        setOrientation(newOrientation);
    }
}

std::unique_ptr<Bestiole> Prevoyante::clone() const
{
    return std::make_unique<Prevoyante>(*this);
}
