<?xml version="1.0"?>
<xsl:stylesheet version="1.0"
                xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                xmlns:str="http://exslt.org/strings"
                xmlns:func="http://exslt.org/functions"
                xmlns:exsl="http://exslt.org/common"
                xmlns:rs="http://www.ribbonsoft.com"
                xmlns:foo="http://foo.com"
                extension-element-prefixes="str exsl func">

<func:function name="rs:replace">
    <xsl:param name="text"/>
    <xsl:param name="from"/>
    <xsl:param name="to"/>
    <func:result>
        <xsl:call-template name="replace-string">
            <xsl:with-param name="text" select="$text"/>
            <xsl:with-param name="from" select="$from"/>
            <xsl:with-param name="to" select="$to"/>
        </xsl:call-template>
    </func:result>
</func:function>

<xsl:template name="replace-string">
    <xsl:param name="text"/>
    <xsl:param name="from"/>
    <xsl:param name="to"/>
    <xsl:variable name="stringText" select="string($text)"/>
    <xsl:choose>
      <xsl:when test="contains($stringText,$from)">
        <xsl:value-of select="substring-before($stringText,$from)"/>
        <xsl:value-of select="$to"/>
        <xsl:call-template name="replace-string">
          <xsl:with-param name="text" select="substring-after($stringText,$from)"/>
          <xsl:with-param name="from" select="$from"/>
          <xsl:with-param name="to" select="$to"/>
        </xsl:call-template>
      </xsl:when>
      <xsl:otherwise>
        <xsl:value-of select="$stringText"/>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>

<xsl:template name="replace_strings">
  <xsl:param name="input_text" />
  <xsl:param name="search"
      select="document('operators.xml')/foo:string_replacement/foo:search" />
  <xsl:variable name="replaced_text">
    <xsl:call-template name="replace-string">
      <xsl:with-param name="text" select="$input_text" />
      <xsl:with-param name="from" select="$search[1]/foo:find" />
      <xsl:with-param name="to" select="$search[1]/foo:replace" />
    </xsl:call-template>
  </xsl:variable>
  <xsl:choose>
    <xsl:when test="$search[2]">
      <xsl:call-template name="replace_strings">
        <xsl:with-param name="input_text" select="$replaced_text" />
        <xsl:with-param name="search" select="$search[position() > 1]" />
      </xsl:call-template>
    </xsl:when>
    <xsl:otherwise>
      <xsl:value-of select="$replaced_text" />
    </xsl:otherwise>
  </xsl:choose>
</xsl:template>

</xsl:stylesheet>