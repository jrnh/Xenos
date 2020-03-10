#include "ProfileMgr.h"
#include <BlackBone/src/BlackBone/Misc/Utils.h>

#define CURRENT_PROFILE L"\\KankerCurrentProfile.xpr"

bool ProfileMgr::Save( const std::wstring& path /*= L""*/)
{
    try
    {
        auto filepath = path.empty() ? (blackbone::Utils::GetExeDirectory() + CURRENT_PROFILE) : path;

        acut::XmlDoc<wchar_t> xml;
        xml.create_document();

        for (auto& imgpath : _config.images)
            xml.append( L"KankerConfig.imagePath" ).value( imgpath );

        xml.set( L"KankerConfig.manualMapFlags", _config.mmapFlags );
        xml.set( L"KankerConfig.procName",       _config.procName.c_str() );
        xml.set( L"KankerConfig.hijack",         _config.hijack );
        xml.set( L"KankerConfig.unlink",         _config.unlink );
        xml.set( L"KankerConfig.erasePE",        _config.erasePE );
        xml.set( L"KankerConfig.close",          _config.close );
        xml.set( L"KankerConfig.krnHandle",      _config.krnHandle );
        xml.set( L"KankerConfig.injIndef",       _config.injIndef );
        xml.set( L"KankerConfig.processMode",    _config.processMode );
        xml.set( L"KankerConfig.injectMode",     _config.injectMode );
        xml.set( L"KankerConfig.delay",          _config.delay );
        xml.set( L"KankerConfig.period",         _config.period );
        xml.set( L"KankerConfig.skip",           _config.skipProc );
        xml.set( L"KankerConfig.procCmdLine",    _config.procCmdLine.c_str() );
        xml.set( L"KankerConfig.initRoutine",    _config.initRoutine.c_str() );
        xml.set( L"KankerConfig.initArgs",       _config.initArgs.c_str() );

        xml.write_document( filepath );
        
        return true;
    }
    catch (const std::runtime_error&)
    {
        return false;
    }
}

bool ProfileMgr::Load( const std::wstring& path /*= L""*/ )
{
    try
    {
        auto filepath = path.empty() ? (blackbone::Utils::GetExeDirectory() + CURRENT_PROFILE) : path;
        if (!acut::file_exists( filepath ))
            return false;

        acut::XmlDoc<wchar_t> xml;
        xml.read_from_file( filepath );

        // Load images in a safe way
        if(xml.has( L"KankerConfig.imagePath" ))
        {
            auto nodes = xml.all_nodes_named( L"KankerConfig.imagePath" );
            for (auto& node : nodes)
                _config.images.emplace_back( node.value() );
        }

        xml.get_if_present( L"KankerConfig.manualMapFlags",  _config.mmapFlags );
        xml.get_if_present( L"KankerConfig.procName",        _config.procName );
        xml.get_if_present( L"KankerConfig.hijack",          _config.hijack );
        xml.get_if_present( L"KankerConfig.unlink",          _config.unlink );
        xml.get_if_present( L"KankerConfig.erasePE",         _config.erasePE );
        xml.get_if_present( L"KankerConfig.close",           _config.close );
        xml.get_if_present( L"KankerConfig.krnHandle",       _config.krnHandle );
        xml.get_if_present( L"KankerConfig.injIndef",        _config.injIndef );
        xml.get_if_present( L"KankerConfig.processMode",     _config.processMode );
        xml.get_if_present( L"KankerConfig.injectMode",      _config.injectMode );
        xml.get_if_present( L"KankerConfig.delay",           _config.delay );
        xml.get_if_present( L"KankerConfig.period",          _config.period );
        xml.get_if_present( L"KankerConfig.skip",            _config.skipProc );
        xml.get_if_present( L"KankerConfig.procCmdLine",     _config.procCmdLine );
        xml.get_if_present( L"KankerConfig.initRoutine",     _config.initRoutine );
        xml.get_if_present( L"KankerConfig.initArgs",        _config.initArgs );

        return true;
    }
    catch (const std::runtime_error&)
    {
        return false;
    }
}
