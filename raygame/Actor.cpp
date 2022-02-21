#include "Actor.h"
#include "Transform2D.h"
#include <string.h>
#include "Collider.h"
#include "Component.h"
#include <iostream>

Actor::Actor()
{
    m_transform = new Transform2D(this);
}

Actor::~Actor()
{
    delete m_transform;
}

Actor::Actor(float x, float y, const char* name = "Actor")
{
    //Initialze default values.
    m_transform = new Transform2D(this);
    m_transform->setLocalPosition({ x,y });
    m_name = name;
}

void Actor::start()
{
    m_started = true;
}

void Actor::onCollision(Actor* other)
{
    for (int i = 0; i < m_componentCount; i++)
        m_components[i]->onCollision(other);
}

Component* Actor::addComponent(Component* component)
{
    // Return null if this component already has an owner.
    Actor* owner = component->getOwner();
    if (owner)
        return nullptr;

    component->assignOwner(this);

    //Create a new array with a size one greater than our old array.
    Component** appendedArray = new Component*[m_componentCount + 1];
    //Copy the values from the old array to the new array.
    for (int i = 0; i < m_componentCount; i++)
    {
        appendedArray[i] = m_components[i];
    }

    if (m_componentCount > 1)
        delete[] m_components;
    else if (m_componentCount == 1)
        delete m_components;

    //Set the last value in the new array to be the actor we want to add.
    appendedArray[m_componentCount] = component;
    //Set old array to hold the values of the new array.
    m_components = appendedArray;
    m_componentCount++;

	return component;
}

bool Actor::removeComponent(Component* component)
{
    //Check to see if the component was null.
    if (!component)
        return false;

    bool componentRemoved = false;
    //Create a new array with a size one less than our old array.
    Component** newArray = new Component*[m_componentCount - 1];
    //Create variable to access tempArray index.
    int j = 0;
    //Copy values from the old array to the new array.
    for (int i = 0; i < m_componentCount; i++)
    {
        if (component != m_components[i])
        {
            newArray[j] = m_components[i];
            j++;
        }
        else
        {
            component->removeOwner();
            componentRemoved = true;
        }
    }
    //Set the old array to the new array.
    if (componentRemoved)
    {
        delete[] m_components;
        m_components = newArray;
        m_componentCount--;
        delete component;
    }
    else
        delete[] newArray;

    //Return whether or not the removal was successful.
    return componentRemoved;
}

bool Actor::removeComponent(const char* name)
{
    //Check to see if the name was null.
    if (!name)
        return false;

    bool componentRemoved = false;
    Component* componentToDelete = nullptr;
    //Create a new array with a size one less than our old array.
    Component** newArray = new Component*[m_componentCount - 1];
    //Create variable to access tempArray index.
    int j = 0;
    //Copy values from the old array to the new array.
    for (int i = 0; i < m_componentCount; i++)
    {
        if (strcmp(m_components[i]->getName(), name) == 0)
        {
            newArray[j] = m_components[i];
            j++;
        }
        else
        {
            delete[] m_components;
            m_components[i]->removeOwner();
            componentToDelete = m_components[i];
            componentRemoved = true;
        }
    }
    //Set the old array to the new array.
    if (componentRemoved)
    {
        m_components = newArray;
        m_componentCount--;
        delete componentToDelete;
    }
    else
        delete[] newArray;

    //Return whether or not the removal was successful.
    return componentRemoved;
}

Component* Actor::getComponent(const char* name)
{
    for (int i = 0; i < m_componentCount; i++)
    {
        // Check to see if the name given is the same name of the component at the current index.
        if (strcmp(m_components[i]->getName(), name) == 0)
            return m_components[i];
    }
}

void Actor::update(float deltaTime)
{
    for (int i = 0; i < m_componentCount; i++) 
    {
        if (!m_components[i]->getStarted())
            m_components[i]->start();

        m_components[i]->update(deltaTime);
    }
}

void Actor::draw()
{
    for (int i = 0; i < m_componentCount; i++)
    {
        if (!m_components[i]->getStarted())
            m_components[i]->start();

        m_components[i]->draw();
    }
}

void Actor::end()
{
    for (int i = 0; i < m_componentCount; i++)
    {
        if (!m_components[i]->getStarted())
            m_components[i]->start();

        m_components[i]->end();
    }

    m_started = false;
}

void Actor::onDestroy()
{
    for (int i = 0; i < m_componentCount; i++)
        m_components[i]->onDestroy();

    //Removes this actor from its parent if it has one.
    if (getTransform()->getParent())
        getTransform()->getParent()->removeChild(getTransform());
}

bool Actor::checkForCollision(Actor* other)
{
    //Call check collision if there is a collider attached to this actor.
    if (m_collider)
        return m_collider->checkCollision(other);

    return false;
}