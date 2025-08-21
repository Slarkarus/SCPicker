#ifndef EVENTS_HPP
#define EVENTS_HPP

enum class Event
{
    Up,
    Down,
    Left,
    Right,
    Space,
    Enter,
    Escape,
    CountOfEvents
};

using EventsArray = std::array<bool, static_cast<std::size_t>(Event::CountOfEvents)>;

#endif // EVENTS_HPP