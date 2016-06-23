//
//  AntiqueVideoFilter.hpp
//  Pods
//
//  Created by Alex.Shi on 16/3/3.
//
//

#ifndef AntiqueVideoFilter_hpp
#define AntiqueVideoFilter_hpp

#include <videocore/filters/IVideoFilter.hpp>

namespace videocore {
    namespace filters {
        class AntiqueVideoFilter : public IVideoFilter {
            
        public:
            AntiqueVideoFilter();
            ~AntiqueVideoFilter();
            
        public:
            virtual void initialize();
            virtual bool initialized() const { return m_initialized; };
            virtual std::string const name() { return "com.videocore.filters.antique"; };
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
            int mToneCurveTextureUniformLocation;
            
            bool m_initialized;
            bool m_bound;
            
        };
    }
}

#endif /* AntiqueVideoFilter_hpp */
