#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H
#include "BaseComponent.h"
#include "Entity.h"
#include <memory>
#include <map>
#include <algorithm>
#include <iostream>

/**
 * @brief The ComponentManager class: Manages the creation and removal of all components. Use this class to add components to entities.
 */
namespace zmc
{
class ComponentManager
{
public:
    ComponentManager();
    /**
     * @brief Adds a component to the entity
     */
    void addComponent(int entityID, std::unique_ptr<BaseComponent> component);
    /**
     * @brief Remove a type of component from all the entities
     */
    void removeComponent(int componentType);
    /**
     * @brief Remove a type of component from all the entities
     */
    void removeComponent(int entityID , int componentType);
    /**
     * @brief Remove a type of component from the entity
     */
    void removeComponentOfEntity(int componentType, Entity &entity);
    /**
     * @brief Removes all of the compoenents from the entity
     * @param entity
     */
    void removeComponentsOfEntity(Entity &entity);
    std::vector<BaseComponent*> getComponentsOfEntity(int entityID);
    template <class Com>
    Com * const getComponentOfEntity(int entityID)
    {
        BaseComponent *c = nullptr;
        for (std::pair<const int, std::unique_ptr<BaseComponent>> &pair : mComponentsMap) {
            if (pair.first == entityID) {
                c = pair.second.get();
                break;
            }
        }
        return dynamic_cast<Com*>(c);
    }

    /**
     * @brief Returns true if the specified entity has the compoenent type
     * @param entityID
     * @param componentType
     * @return
     */
    bool hasComponent(int entityID, int componentType);

    /**
     * @brief Removes all of the components from the ComponentManager
     */
    void clean();

    std::vector<BaseComponent*> getComponentsInGroup(int groupIdentifier);

private:
    /**
     * @brief Entity ID : Component
     */
    std::map<int, std::unique_ptr<BaseComponent>> mComponentsMap;
};
}
#endif // COMPONENTMANAGER_H
