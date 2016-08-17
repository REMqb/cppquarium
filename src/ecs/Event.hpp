#pragma once

namespace ecs {

    template<typename SourceT_>
    class Event{
        public:
            using SourceT = SourceT_;

            SourceT& getSource();

        protected:
            Event(SourceT& source) : source(source) {
            }

        private:
            SourceT& source;

    };

    template<typename SourceT> SourceT& Event<SourceT>::getSource(){
        return source;
    }

}
