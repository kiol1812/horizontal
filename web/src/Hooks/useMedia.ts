import { useState, useEffect } from "react";

export const LAYOUT = {
    MOBILE: 'mobile',
    TABLET: 'tablet',
    DESKTOP: 'desktop',
}

export const MAX_MOBILE_WIDTH = 710;
export const MAX_TABLLET_WIDTH = 1024;
export const MAX_DESKTOP_M_WIDTH = 1440;

const useMedia = () => {
    const [currentLayout, setCurrentLayout] = useState(LAYOUT.MOBILE);
    useEffect(()=>{
        const handleWindowWidth = () => {
            if(window.innerWidth<MAX_MOBILE_WIDTH) setCurrentLayout(LAYOUT.MOBILE);
            else if(window.innerWidth<MAX_TABLLET_WIDTH) setCurrentLayout(LAYOUT.TABLET);
            else setCurrentLayout(LAYOUT.DESKTOP);
        };
        handleWindowWidth();

        window.addEventListener('resize', handleWindowWidth);

        return () => {
            window.removeEventListener('resize', handleWindowWidth);
        };
    }, []);

    return {
        isMobile: currentLayout === LAYOUT.MOBILE,
        isTablet: currentLayout === LAYOUT.TABLET,
        isDesktop: currentLayout === LAYOUT.DESKTOP,
    };
}

export default useMedia;
