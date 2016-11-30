
/*
** Started by Alexis Mongin 2016-11-30
*/

/*

Interface for the different systems !

*/

class ISystem
{
    ISystem() = delete;
    virtual ~ISystem();

    ISystem(const ISystem &) = delete;
    ISystem &operator=(const ISystem &) = delete;

    virtual void	update(WorldData &, WorldFactories &) = 0;
};
