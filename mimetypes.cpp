#include <mimetypes.h>
#include <apptypes.h>
using namespace std;

MapStrStr * contentType = NULL;
//QMap<QString,QString>      * contentType = 0;

void setupContentTypes()
{
	if ( !contentType )
	{	
    contentType = new MapStrStr();
    (*contentType)[QString("a")]= QString("application/octet-stream");
    (*contentType)[QString("aab")]= QString("application/x-authorware-bin");
    (*contentType)[QString("aam")]= QString("application/x-authorware-map");
    (*contentType)[QString("aas")]= QString("application/x-authorware-seg");
    (*contentType)[QString("ai")]= QString("application/postscript");
    (*contentType)[QString("aif")]= QString("audio/x-aiff");
    (*contentType)[QString("aifc")]= QString("audio/x-aiff");
    (*contentType)[QString("aiff")]= QString("audio/x-aiff");
    (*contentType)[QString("asc")]= QString("text/plain");
    (*contentType)[QString("asf")]= QString("video/x-ms-asf");
    (*contentType)[QString("asx")]= QString("video/x-ms-asf");
    (*contentType)[QString("au")]= QString("audio/basic");
    (*contentType)[QString("avi")]= QString("video/x-msvideo");
    (*contentType)[QString("bcpio")]= QString("application/x-bcpio");
    (*contentType)[QString("bin")]= QString("application/octet-stream");
    (*contentType)[QString("bmp")]= QString("image/bmp");
    (*contentType)[QString("cdf")]= QString("application/x-netcdf");
    (*contentType)[QString("class")]= QString("application/x-java-vm");
    (*contentType)[QString("cpio")]= QString("application/x-cpio");
    (*contentType)[QString("cpt")]= QString("application/mac-compactpro");
    (*contentType)[QString("crl")]= QString("application/x-pkcs7-crl");
    (*contentType)[QString("crt")]= QString("application/x-x509-ca-cert");
    (*contentType)[QString("csh")]= QString("application/x-csh");
    (*contentType)[QString("css")]= QString("text/css");
    (*contentType)[QString("dcr")]= QString("application/x-director");
    (*contentType)[QString("dir")]= QString("application/x-director");
    (*contentType)[QString("djv")]= QString("image/vnd.djvu");
    (*contentType)[QString("djvu")]= QString("image/vnd.djvu");
    (*contentType)[QString("dll")]= QString("application/octet-stream");
    (*contentType)[QString("dms")]= QString("application/octet-stream");
    (*contentType)[QString("doc")]= QString("application/msword");
    (*contentType)[QString("dtd")]= QString("text/xml");
    (*contentType)[QString("dump")]= QString("application/octet-stream");
    (*contentType)[QString("dvi")]= QString("application/x-dvi");
    (*contentType)[QString("dxr")]= QString("application/x-director");
    (*contentType)[QString("eps")]= QString("application/postscript");
    (*contentType)[QString("etx")]= QString("text/x-setext");
    (*contentType)[QString("exe")]= QString("application/octet-stream");
    (*contentType)[QString("ez")]= QString("application/andrew-inset");
    (*contentType)[QString("fgd")]= QString("application/x-director");
    (*contentType)[QString("fh")]= QString("image/x-freehand");
    (*contentType)[QString("fh4")]= QString("image/x-freehand");
    (*contentType)[QString("fh5")]= QString("image/x-freehand");
    (*contentType)[QString("fh7")]= QString("image/x-freehand");
    (*contentType)[QString("fhc")]= QString("image/x-freehand");
    (*contentType)[QString("gif")]= QString("image/gif");
    (*contentType)[QString("gtar")]= QString("application/x-gtar");
    (*contentType)[QString("hdf")]= QString("application/x-hdf");
    (*contentType)[QString("hqx")]= QString("application/mac-binhex40");
    (*contentType)[QString("htm")]= QString("text/html; charset)]=%s");
    (*contentType)[QString("html")]= QString("text/html; charset)]=%s");
    (*contentType)[QString("ice")]= QString("x-conference/x-cooltalk");
    (*contentType)[QString("ief")]= QString("image/ief");
    (*contentType)[QString("iges")]= QString("model/iges");
    (*contentType)[QString("igs")]= QString("model/iges");
    (*contentType)[QString("iv")]= QString("application/x-inventor");
    (*contentType)[QString("jar")]= QString("application/x-java-archive");
    (*contentType)[QString("jfif")]= QString("image/jpeg");
    (*contentType)[QString("jpe")]= QString("image/jpeg");
    (*contentType)[QString("jpeg")]= QString("image/jpeg");
    (*contentType)[QString("jpg")]= QString("image/jpeg");
    (*contentType)[QString("js")]= QString("application/x-javascript");
    (*contentType)[QString("kar")]= QString("audio/midi");
    (*contentType)[QString("latex")]= QString("application/x-latex");
    (*contentType)[QString("lha")]= QString("application/octet-stream");
    (*contentType)[QString("lzh")]= QString("application/octet-stream");
    (*contentType)[QString("m3u")]= QString("audio/x-mpegurl");
    (*contentType)[QString("man")]= QString("application/x-troff-man");
    (*contentType)[QString("mathml")]= QString("application/mathml+xml");
    (*contentType)[QString("me")]= QString("application/x-troff-me");
    (*contentType)[QString("mesh")]= QString("model/mesh");
    (*contentType)[QString("mid")]= QString("audio/midi");
    (*contentType)[QString("midi")]= QString("audio/midi");
    (*contentType)[QString("mif")]= QString("application/vnd.mif");
    (*contentType)[QString("mime")]= QString("message/rfc822");
    (*contentType)[QString("mml")]= QString("application/mathml+xml");
    (*contentType)[QString("mov")]= QString("video/quicktime");
    (*contentType)[QString("movie")]= QString("video/x-sgi-movie");
    (*contentType)[QString("mp2")]= QString("audio/mpeg");
    (*contentType)[QString("mp3")]= QString("audio/mpeg");
    (*contentType)[QString("mp4")]= QString("video/mp4");
    (*contentType)[QString("mpe")]= QString("video/mpeg");
    (*contentType)[QString("mpeg")]= QString("video/mpeg");
    (*contentType)[QString("mpg")]= QString("video/mpeg");
    (*contentType)[QString("mpga")]= QString("audio/mpeg");
    (*contentType)[QString("ms")]= QString("application/x-troff-ms");
    (*contentType)[QString("msh")]= QString("model/mesh");
    (*contentType)[QString("mv")]= QString("video/x-sgi-movie");
    (*contentType)[QString("mxu")]= QString("video/vnd.mpegurl");
    (*contentType)[QString("nc")]= QString("application/x-netcdf");
    (*contentType)[QString("o")]= QString("application/octet-stream");
    (*contentType)[QString("oda")]= QString("application/oda");
        (*contentType)[QString("out")]= QString("application/x-ogg");
        (*contentType)[QString("txt")]= QString("text/plain");
    (*contentType)[QString("pac")]= QString("application/x-ns-proxy-autoconfig");
    (*contentType)[QString("pbm")]= QString("image/x-portable-bitmap");
    (*contentType)[QString("pdb")]= QString("chemical/x-pdb");
    (*contentType)[QString("pdf")]= QString("application/pdf");
    (*contentType)[QString("pgm")]= QString("image/x-portable-graymap");
    (*contentType)[QString("pgn")]= QString("application/x-chess-pgn");
    (*contentType)[QString("png")]= QString("image/png");
    (*contentType)[QString("pnm")]= QString("image/x-portable-anymap");
    (*contentType)[QString("ppm")]= QString("image/x-portable-pixmap");
    (*contentType)[QString("ppt")]= QString("application/vnd.ms-powerpoint");
    (*contentType)[QString("ps")]= QString("application/postscript");
    (*contentType)[QString("qt")]= QString("video/quicktime");
    (*contentType)[QString("ra")]= QString("audio/x-realaudio");
    (*contentType)[QString("ram")]= QString("audio/x-pn-realaudio");
    (*contentType)[QString("ras")]= QString("image/x-cmu-raster");
    (*contentType)[QString("rdf")]= QString("application/rdf+xml");
    (*contentType)[QString("rgb")]= QString("image/x-rgb");
    (*contentType)[QString("rm")]= QString("audio/x-pn-realaudio");
    (*contentType)[QString("roff")]= QString("application/x-troff");
    (*contentType)[QString("rpm")]= QString("audio/x-pn-realaudio-plugin");
    (*contentType)[QString("rss")]= QString("application/rss+xml");
    (*contentType)[QString("rtf")]= QString("text/rtf");
    (*contentType)[QString("rtx")]= QString("text/richtext");
    (*contentType)[QString("sgm")]= QString("text/sgml");
    (*contentType)[QString("sgml")]= QString("text/sgml");
    (*contentType)[QString("sh")]= QString("application/x-sh");
    (*contentType)[QString("shar")]= QString("application/x-shar");
    (*contentType)[QString("silo")]= QString("model/mesh");
    (*contentType)[QString("sit")]= QString("application/x-stuffit");
    (*contentType)[QString("skd")]= QString("application/x-koan");
    (*contentType)[QString("skm")]= QString("application/x-koan");
    (*contentType)[QString("skp")]= QString("application/x-koan");
    (*contentType)[QString("skt")]= QString("application/x-koan");
    (*contentType)[QString("smi")]= QString("application/smil");
    (*contentType)[QString("smil")]= QString("application/smil");
    (*contentType)[QString("snd")]= QString("audio/basic");
    (*contentType)[QString("so")]= QString("application/octet-stream");
    (*contentType)[QString("spl")]= QString("application/x-futuresplash");
    (*contentType)[QString("src")]= QString("application/x-wais-source");
    (*contentType)[QString("stc")]= QString("application/vnd.sun.xml.calc.template");
    (*contentType)[QString("std")]= QString("application/vnd.sun.xml.draw.template");
    (*contentType)[QString("sti")]= QString("application/vnd.sun.xml.impress.template");
    (*contentType)[QString("stw")]= QString("application/vnd.sun.xml.writer.template");
    (*contentType)[QString("sv4cpio")]= QString("application/x-sv4cpio");
    (*contentType)[QString("sv4crc")]= QString("application/x-sv4crc");
    (*contentType)[QString("svg")]= QString("image/svg+xml");
    (*contentType)[QString("svgz")]= QString("image/svg+xml");
    (*contentType)[QString("swf")]= QString("application/x-shockwave-flash");
    (*contentType)[QString("sxc")]= QString("application/vnd.sun.xml.calc");
    (*contentType)[QString("sxd")]= QString("application/vnd.sun.xml.draw");
    (*contentType)[QString("sxg")]= QString("application/vnd.sun.xml.writer.global");
    (*contentType)[QString("sxi")]= QString("application/vnd.sun.xml.impress");
    (*contentType)[QString("sxm")]= QString("application/vnd.sun.xml.math");
    (*contentType)[QString("sxw")]= QString("application/vnd.sun.xml.writer");
    (*contentType)[QString("t")]= QString("application/x-troff");
    (*contentType)[QString("tar")]= QString("application/x-tar");
    (*contentType)[QString("tcl")]= QString("application/x-tcl");
    (*contentType)[QString("tex")]= QString("application/x-tex");
    (*contentType)[QString("texi")]= QString("application/x-texinfo");
    (*contentType)[QString("texinfo")]= QString("application/x-texinfo");
    (*contentType)[QString("tif")]= QString("image/tiff");
    (*contentType)[QString("tiff")]= QString("image/tiff");
    (*contentType)[QString("tr")]= QString("application/x-troff");
    (*contentType)[QString("tsp")]= QString("application/dsptype");
    (*contentType)[QString("tsv")]= QString("text/tab-separated-values");
    (*contentType)[QString("txt")]= QString("text/plain; charset)]=%s");
    (*contentType)[QString("ustar")]= QString("application/x-ustar");
    (*contentType)[QString("vcd")]= QString("application/x-cdlink");
    (*contentType)[QString("vrml")]= QString("model/vrml");
    (*contentType)[QString("vx")]= QString("video/x-rad-screenplay");
    (*contentType)[QString("wav")]= QString("audio/x-wav");
    (*contentType)[QString("wax")]= QString("audio/x-ms-wax");
    (*contentType)[QString("wbmp")]= QString("image/vnd.wap.wbmp");
    (*contentType)[QString("wbxml")]= QString("application/vnd.wap.wbxml");
    (*contentType)[QString("wm")]= QString("video/x-ms-wm");
    (*contentType)[QString("wma")]= QString("audio/x-ms-wma");
    (*contentType)[QString("wmd")]= QString("application/x-ms-wmd");
    (*contentType)[QString("wml")]= QString("text/vnd.wap.wml");
    (*contentType)[QString("wmlc")]= QString("application/vnd.wap.wmlc");
    (*contentType)[QString("wmls")]= QString("text/vnd.wap.wmlscript");
    (*contentType)[QString("wmlsc")]= QString("application/vnd.wap.wmlscriptc");
    (*contentType)[QString("wmv")]= QString("video/x-ms-wmv");
    (*contentType)[QString("wmx")]= QString("video/x-ms-wmx");
    (*contentType)[QString("wmz")]= QString("application/x-ms-wmz");
    (*contentType)[QString("wrl")]= QString("model/vrml");
    (*contentType)[QString("wsrc")]= QString("application/x-wais-source");
    (*contentType)[QString("wvx")]= QString("video/x-ms-wvx");
    (*contentType)[QString("xbm")]= QString("image/x-xbitmap");
    (*contentType)[QString("xht")]= QString("application/xhtml+xml");
    (*contentType)[QString("xhtml")]= QString("application/xhtml+xml");
    (*contentType)[QString("xls")]= QString("application/vnd.ms-excel");
    (*contentType)[QString("xml")]= QString("text/xml");
    (*contentType)[QString("xpm")]= QString("image/x-xpixmap");
    (*contentType)[QString("xsl")]= QString("text/xml");
    (*contentType)[QString("xul")]= QString("application/vnd.mozilla.xul+xml");
    (*contentType)[QString("xwd")]= QString("image/x-xwindowdump");
    (*contentType)[QString("xyz")]= QString("chemical/x-xyz");
    (*contentType)[QString("zip")]= QString("application/zip");
	}
}

QString identifyContentType( char *dUrl )
{
// url is null terminated	
        static const char *empty="";
	if(!dUrl)
		return (const char *)empty;
	char *url = dUrl;
	while( *url != '\0' && *url != '.' )
	{
		url++;
	}
	if( *url == '.' )
		url++;
	else
		return (const char *)empty;

	MapStrStr::iterator i = contentType->find(url);
	if( i != contentType->end() )
	{
        return i.value();
	}
	return (const char *)empty;
}
