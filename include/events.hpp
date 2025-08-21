#ifndef EVENTS_HPP
#define EVENTS_HPP

using EventsArray = std::array<bool, static_cast<std::size_t>(Event::CountOfEvents)>;

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

#endif // EVENTS_HPP