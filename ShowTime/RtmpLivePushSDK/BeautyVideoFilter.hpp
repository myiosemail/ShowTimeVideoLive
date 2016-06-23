//
//  BeautyVideoFilter.hpp
//  Pods
//
//  Created by Alex.Shi on 16/3/2.
//
//

#ifndef BeautyVideoFilter_hpp
#define BeautyVideoFilter_hpp

#include <videocore/filters/IVideoFilter.hpp>

namespace videocore {
    namespace filters {
        class BeautyVideoFilter : public IVideoFilter {
            
        public:
            BeautyVideoFilter();
            ~BeautyVideoFilter();
            
        public:
            virtual void initialize();
            virtual bool initialized() const { return m_initialized; };
            virtual std::string const name() { return "com.videocore.filters.beauty"; };
            virtual void bind();
            virtual void unbind();
            
        public:
            
            const char * const vertexKernel() const ;
            const char * const pixelKernel() const ;
            
        private:
            static bool registerFilter();
            static bool s_registered;
        private:
            
            unsigned int m_vao;
            unsigned int m_uMatrix;
            unsigned int m_uWH;
            unsigned int m_beautyParam;
            unsigned int m_uWidth;
            unsigned int m_uHeight;
            
            bool m_initialized;
            bool m_bound;
            
        };
    }
}

#endif /* BeautyVideoFilter_hpp */
