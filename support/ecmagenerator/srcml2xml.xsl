<?xml version="1.0" encoding="UTF-8"?>

<xsl:stylesheet version="1.0"
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:srcml="http://www.sdml.info/srcML/src"
    xmlns:cpp="http://www.sdml.info/srcML/cpp"
    xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
    xmlns:rs="http://www.ribbonsoft.com"
    xmlns:func="http://exslt.org/functions"
    exclude-result-prefixes="cpp srcml func"
    extension-element-prefixes="func"
    >

    <xsl:include href="replace.xsl"/>
    
    <xsl:output method="xml" />
    
    <xsl:key name="function"
        match="//srcml:function/srcml:name/text() | //srcml:function_decl/srcml:name/text()"
        use="." />

    <xsl:template match="/">
        <!--
        <xsl:for-each select="key('function', 'rotate')">
            <xsl:message>
                <xsl:value-of select="." />
            </xsl:message>
        </xsl:for-each>
        -->
        <xsl:apply-templates />
    </xsl:template>

    <xsl:template match="srcml:unit">
        <unit>
            <xsl:apply-templates select="srcml:class_decl" />
            <xsl:apply-templates select="srcml:class" />
        </unit>
    </xsl:template>

    <xsl:template match="srcml:class_decl">
        <class_decl name="{srcml:name/text()}"/>
     </xsl:template>

    <xsl:template match="srcml:class">
        <xsl:variable name="name" select="srcml:name/text()"/>
        <xsl:variable name="scriptable"
          select="contains(preceding-sibling::srcml:comment[1]/text(), '\scriptable')"/>
        <class name="{$name}"
            xsi:noNamespaceSchemaLocation="../class.xsd"
            isCopyable="{contains(preceding-sibling::srcml:comment[1]/text(), '\copyable')}"
            hasShell="{contains(preceding-sibling::srcml:comment[1]/text(), '\generateScriptShell')}"
            sharedPointerSupport="{contains(preceding-sibling::srcml:comment[1]/text(), '\sharedPointerSupport')}"
            isQObject="{srcml:block/srcml:private/srcml:macro/srcml:name/text() = 'Q_OBJECT' or
                srcml:block/srcml:private/srcml:function_decl/srcml:type/srcml:name/text() = 'Q_OBJECT' }"
            hasStreamOperator="{contains(preceding-sibling::srcml:comment[1]/text(), '\hasStreamOperator') or boolean(/srcml:unit/srcml:function_decl/srcml:name[text() = 'operator&lt;&lt;'])}"
            isAbstract="{boolean(.//srcml:specifier[ translate(normalize-space(text()), ' ', '') = '=0' ])
                or contains(preceding-sibling::srcml:comment[1]/text(), '\abstract')}"
            isScriptable="{$scriptable}"
            >
            
          <xsl:if test="$scriptable">
            <xsl:for-each select="srcml:super/srcml:name">
                <xsl:variable name="baseClassName">
                    <xsl:apply-templates select="." mode="alltextnsp" />
                </xsl:variable>

                <baseClass>
                    <xsl:attribute name="name">
                        <xsl:value-of select="$baseClassName"/>
                    </xsl:attribute>
                    <xsl:attribute name="specifier">
                        <xsl:choose>
                          <xsl:when test="name(preceding-sibling::*[1])='specifier'">
                            <xsl:apply-templates 
                                select="preceding-sibling::*[1]/text()" mode="alltext" />
                          </xsl:when>
                          <xsl:otherwise>
                            <xsl:text>private</xsl:text>
                          </xsl:otherwise>
                        </xsl:choose>
                    </xsl:attribute>
                </baseClass>
            </xsl:for-each>
            
            <!--  enums -->
            <xsl:for-each select="srcml:block/srcml:public/srcml:enum">
                <enum name="{srcml:name/text()}">
                    <xsl:for-each select="srcml:block/srcml:expr/srcml:name[1]">
                        <value name="{text()}"/>
                    </xsl:for-each>
                </enum>
            </xsl:for-each>
            
            <!-- constructor -->
            <xsl:if test="srcml:block/srcml:public/srcml:constructor
                    | srcml:block/srcml:public/srcml:constructor_decl">
                <constructor>
                    <xsl:apply-templates select="srcml:block/srcml:public/srcml:constructor
                    | srcml:block/srcml:public/srcml:constructor_decl" />
                </constructor>
            </xsl:if>

            <!-- methods -->
            <xsl:variable name="class" select="."/>
            <xsl:for-each
                select="srcml:block/srcml:public/srcml:function/srcml:name[generate-id(text())=generate-id(key('function',text()))]
                | srcml:block/srcml:public/srcml:function_decl/srcml:name[generate-id(text())=generate-id(key('function',text()))]
                | srcml:block/srcml:protected/srcml:function/srcml:name[generate-id(text())=generate-id(key('function',text()))]
                | srcml:block/srcml:protected/srcml:function_decl/srcml:name[generate-id(text())=generate-id(key('function',text()))]">
                    <xsl:variable name="methodName" select="text()"/>
                    <xsl:variable name="f"
                        select="$class/srcml:block/srcml:public/srcml:function[srcml:name/text()=$methodName]"/>
                    <xsl:variable name="fd"
                        select="$class/srcml:block/srcml:public/srcml:function_decl[srcml:name/text()=$methodName]" />
                    <xsl:variable name="fp"
                        select="$class/srcml:block/srcml:protected/srcml:function[srcml:name/text()=$methodName]"/>
                    <xsl:variable name="fdp"
                        select="$class/srcml:block/srcml:protected/srcml:function_decl[srcml:name/text()=$methodName]" />
                                          
                    <xsl:if test="rs:isScriptable(..) and not(rs:isSignal(..)) and not (boolean(preceding-sibling::srcml:type/srcml:name[text()='friend']))">
                        <xsl:variable name="specifier">
                            <xsl:choose>
                              <xsl:when test="ancestor::srcml:public">
                                <xsl:text>public</xsl:text>
                              </xsl:when>
                              <xsl:when test="ancestor::srcml:protected">
                                <xsl:text>protected</xsl:text>
                              </xsl:when>
                            </xsl:choose>
                        </xsl:variable>

                        <method name="{$methodName}" cppName="{$methodName}" specifier="{$specifier}">
                            <xsl:attribute name="isStatic">
                                <xsl:value-of select="boolean(preceding-sibling::srcml:type/srcml:name[text()='static']) or boolean(preceding-sibling::srcml:type/srcml:specifier[text()='static'])"/>
                            </xsl:attribute>
                            <xsl:attribute name="isVirtual">
                                <xsl:value-of select="boolean(preceding-sibling::srcml:type/srcml:name[text()='virtual'])"/>
                            </xsl:attribute>
                            <xsl:attribute name="isScriptOverwritable">
                                <xsl:value-of select="rs:isScriptOverwritable(..)"/>
                            </xsl:attribute>
                            <xsl:apply-templates select="$f" />
                            <xsl:apply-templates select="$fd" />
                            <xsl:apply-templates select="$fp" />
                            <xsl:apply-templates select="$fdp" />
                        </method>
                    </xsl:if>
            </xsl:for-each>
            
            <!-- properties -->
            <xsl:apply-templates select="srcml:block/srcml:public/srcml:decl_stmt" />
        </xsl:if>
        
        </class>
    </xsl:template>

    <xsl:template match="srcml:function|srcml:function_decl">
        <xsl:if test="rs:isScriptable(.)">
            <variant>
                <xsl:variable name="returnType">
                    <xsl:if test="boolean(srcml:type/srcml:name[text()='const'])">
                        <xsl:text>const </xsl:text>
                    </xsl:if>
                    <xsl:apply-templates select="srcml:type/srcml:name[last()]"
                        mode="alltext"/>
                    <xsl:value-of select="srcml:type/text()[last()]"/>
                </xsl:variable>
                <xsl:attribute name="returnType">
                    <xsl:value-of select="rs:fixType($returnType)"/>
                </xsl:attribute>
                <xsl:attribute name="isPureVirtual">
                    <xsl:value-of select="rs:replace(rs:replace(srcml:specifier/text(), ' ', ''), '&#x0A;', '')='=0'"/>
                </xsl:attribute>
                <xsl:apply-templates select="srcml:parameter_list/srcml:param" />
            </variant>
        </xsl:if>
    </xsl:template>

    <xsl:template match="text()" />

    <xsl:template match="srcml:constructor | srcml:constructor_decl">
        <xsl:if test="rs:isScriptable(.)">
            <variant>
                <xsl:apply-templates select="./srcml:parameter_list/srcml:param" />
            </variant>
        </xsl:if>
    </xsl:template>

    <xsl:template match="srcml:param">
       <xsl:variable name="type">
         <xsl:apply-templates mode="alltext"
             select="srcml:decl/srcml:type/srcml:name[last()]" />
         <xsl:value-of select="srcml:decl/srcml:type/text()[last()]" />
       </xsl:variable>
       <xsl:element name="arg">
         <xsl:attribute name="type">
             <xsl:value-of select="rs:fixType($type)"/>
         </xsl:attribute>
         <xsl:attribute name="typeName">
            <xsl:value-of select="rs:fixType(rs:replace($type, '&amp;', ''))"/>
         </xsl:attribute>
         <xsl:attribute name="name">
             <xsl:value-of select="srcml:decl/srcml:name/text()" />
         </xsl:attribute>
         <xsl:if test="srcml:decl/srcml:init">
             <xsl:attribute name="hasDefault">
                  <xsl:value-of select="'true'" />
             </xsl:attribute>
             <xsl:attribute name="default">
                 <xsl:apply-templates mode="alltext" select="srcml:decl/srcml:init/srcml:expr" />
                  <!--
                     <xsl:value-of select="srcml:decl/srcml:init/srcml:expr/text()" />
                   -->
             </xsl:attribute>
         </xsl:if>
         <xsl:attribute name="isConst">
           <xsl:value-of select="boolean(srcml:decl/srcml:type/srcml:name[text()='const']) or boolean(srcml:decl/srcml:type/srcml:specifier[text()='const'])" />
         </xsl:attribute>
       </xsl:element>
    </xsl:template>

    <xsl:template match="text()" mode="alltext">
        <xsl:value-of select="normalize-space(.)" />
        <xsl:text> </xsl:text>
    </xsl:template>

    <xsl:template match="text()" mode="alltextnsp">
        <xsl:value-of select="normalize-space(.)" />
    </xsl:template>

    <!--
      Properties:
    -->
    <xsl:template match="srcml:public/srcml:decl_stmt">
        <xsl:variable name="comment"
            select="preceding-sibling::srcml:comment[1]/text()" />

        <xsl:variable name="type">
            <xsl:apply-templates mode="alltext"
                select="srcml:decl/srcml:type/srcml:name[last()]" />
        </xsl:variable>

        <xsl:choose>
            <xsl:when test="contains($comment, '\getter')">

                <property name="{srcml:decl/srcml:name/text()}"
                    type="{$type}">
                    <xsl:attribute name="cppGetter">
                        <xsl:value-of
                            select="substring-before( substring-after($comment, '\getter{'), '}')" />
                    </xsl:attribute>
                    <xsl:if test="contains($comment, '\setter')">
                        <xsl:attribute name="cppSetter">
                            <xsl:value-of
                                select="substring-before( substring-after($comment, '\setter{'), '}')" />        
                        </xsl:attribute>
                    </xsl:if>
                </property>
            </xsl:when>
            <xsl:when test="srcml:decl/srcml:type/srcml:name[text()='const']">
                <property
                    name="{srcml:decl/srcml:name/text()}"
                    type="{$type}"
                    isConst="true"
                    isStatic="{boolean(srcml:decl/srcml:type/srcml:name[text()='static']) or boolean(srcml:decl/srcml:type/srcml:specifier[text()='static'])}"
                />
            </xsl:when>
            <xsl:when test="(srcml:decl/srcml:type/srcml:name[text()='static'] or srcml:decl/srcml:type/srcml:specifier[text()='static']) and not(srcml:decl/srcml:argument_list)">
                <property
                    name="{srcml:decl/srcml:name/text()}"
                    type="{$type}"
                    isConst="{boolean(srcml:decl/srcml:type/srcml:name[text()='const'])}"
                    isStatic="true"
                />
            </xsl:when>
        </xsl:choose>
    </xsl:template>

    <func:function name="rs:isSignal">
        <xsl:param name="node" />
        <func:result select="boolean($node/preceding-sibling::srcml:label/srcml:name[text()='signals'])"/>
    </func:function>
    
    <func:function name="rs:isScriptable">
        <xsl:param name="node" />
        <func:result select="($node/ancestor::srcml:public or $node/ancestor::srcml:protected)
            and not($node/ancestor::srcml:typedef)
            and not(contains($node/preceding-sibling::srcml:*[1]/text(), '\nonscriptable'))"/>
    </func:function>

    <func:function name="rs:isScriptOverwritable">
        <xsl:param name="node" />
        <func:result select="not(contains($node/preceding-sibling::srcml:*[1]/text(), '\nonscriptoverwritable'))"/>
    </func:function>

    <func:function name="rs:fixType">
        <xsl:param name="type" />
        <func:result select="normalize-space(rs:replace($type, ' :: ', '::'))"/>
    </func:function>

</xsl:stylesheet>
