<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:func="http://exslt.org/functions"
    xmlns:rs="http://www.ribbonsoft.com"
    extension-element-prefixes="func"
    >
    
    <func:function name="rs:query">
        <xsl:param name="file" />
        <xsl:param name="key" />
        <xsl:param name="default" />
        <func:result>
            <xsl:choose>
	            <xsl:when test="document($file)/dict/entry[@key = $key]">
	                <xsl:value-of select="document($file)/dict/entry[@key = $key]/@value" />
	            </xsl:when>
	            <xsl:otherwise><xsl:value-of select="$default"/></xsl:otherwise>
            </xsl:choose>            
        </func:result>

    </func:function>

</xsl:stylesheet>
