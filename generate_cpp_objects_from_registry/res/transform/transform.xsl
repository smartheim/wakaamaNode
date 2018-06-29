<xsl:stylesheet version="2.0"
                xmlns:xs="http://www.w3.org/2001/XMLSchema"
                xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                xmlns:functx="http://www.functx.com"
                xmlns:fun="http://www.functx.com"
                exclude-result-prefixes="xs functx fun"
                >

<xsl:import href="functx-1.0-nodoc-2007-01.xsl"/>
<xsl:strip-space elements="*"/>
<xsl:output omit-xml-declaration="no" indent="yes" method="xml" cdata-section-elements="description"/>

<xsl:variable name='newline'><xsl:text>
</xsl:text></xsl:variable>

<!-- special cases for the name of a resource -->
<xsl:function name="fun:getName" as="xs:string" xmlns:fun="http://www.functx.com">
  <xsl:param name="arg" as="xs:string"/> 
  <xsl:param name="objectID" as="xs:string"/> 
  <xsl:param name="resourceID" as="xs:string"/> 
 <xsl:choose>
    <xsl:when test="number($objectID)=12 and number($resourceID)=41">
        <xsl:sequence select="'MulticastPacketsSend'"/>
    </xsl:when>
    <xsl:when test="number($objectID)=12 and number($resourceID)=44">
        <xsl:sequence select="'BroadcastPacketsReceived'"/>
    </xsl:when>
    <xsl:when test="number($objectID)=10242">
        <xsl:sequence select="functx:words-to-camel-case(replace(replace($arg,'3-Phase','ThreePhase'),'[^a-zA-Z0-9]',''))"/>
    </xsl:when>
    <xsl:when test="number($objectID)=3347 and number($resourceID)=5501">
        <xsl:sequence select="'DigitalInputStateTransitions'"/>
    </xsl:when>
    <xsl:otherwise>
        <xsl:sequence select="functx:words-to-camel-case(replace($arg,'[^a-zA-Z0-9]',''))"/>
    </xsl:otherwise>
 </xsl:choose>
</xsl:function>

<xsl:function name="fun:getOP" as="xs:string" xmlns:fun="http://www.functx.com">
  <xsl:param name="arg" as="xs:string"/> 
  <xsl:param name="objectID" as="xs:string"/> 
  <xsl:param name="resourceID" as="xs:string"/> 
 <xsl:choose>
    <xsl:when test="number($objectID)=3379 and number($resourceID)=2">
        <xsl:sequence select="'O_RES_R'"/>
    </xsl:when>
    <xsl:otherwise>
        <xsl:sequence select="concat('O_RES_', $arg)"/>
    </xsl:otherwise>
 </xsl:choose>
</xsl:function>

<xsl:template name="substring">
    <xsl:param name="text" />
    <xsl:call-template name="row">
        <xsl:with-param name="text" select="$text" />
    </xsl:call-template>
</xsl:template>

<xsl:template name="row">
    <xsl:param name="text" />
    <xsl:param name="storage" />
    <xsl:param name="count" select="0" />
    <xsl:param name="total" select="70" />
    <xsl:choose>
        <xsl:when test="$count &lt; $total and $text != ''">
            <xsl:variable name="word">
                <xsl:choose>
                    <xsl:when test="contains($text, ' ')">
                        <xsl:value-of select="substring-before($text, ' ')" />
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:value-of select="$text" />
                    </xsl:otherwise>
                </xsl:choose>
            </xsl:variable>
            <xsl:call-template name="row">
                <xsl:with-param name="text" select="substring-after($text, ' ')" />
                <xsl:with-param name="storage" select="concat($storage, ' ', $word)" />
                <xsl:with-param name="count" select="$count + string-length($word)" />
            </xsl:call-template>
        </xsl:when>
        <xsl:otherwise>
 * <xsl:value-of select="$storage" />
            <xsl:if test="$text != ''">
                <xsl:call-template name="substring">
                    <xsl:with-param name="text" select="$text" />
                </xsl:call-template>
            </xsl:if>
        </xsl:otherwise>
    </xsl:choose>
</xsl:template>

  <xsl:template match="/*">
    <xsl:apply-templates select="node()"/>
  </xsl:template>

  <xsl:template match="@*|node()">
    <xsl:copy>
      <xsl:apply-templates select="@*|node()"/>
    </xsl:copy>
  </xsl:template>
  
  <xsl:template match="Object">
  <xsl:variable name="objectid" select="self::node()/ObjectID" />
  <xsl:if test="$objectid gt '0'">
  <xsl:variable name="objectname">LwM2MObject</xsl:variable>
  <xsl:variable name="instancename">LwM2MObject<xsl:value-of select="ObjectID"/>Instance</xsl:variable>
	<xsl:result-document method="text" href="{ObjectID}.h">#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id<xsl:value-of select="ObjectID"/> {
// Custom, overrideable types for Opaque and String resources
<xsl:for-each select="Resources/Item">
    <xsl:variable name="resid" select="self::node()/@ID" />
    <xsl:variable name="name"><xsl:value-of select="fun:getName(Name, $objectid, $resid)" /></xsl:variable>
    <xsl:choose>
    <xsl:when test="self::node()/Type='Opaque'">
    #ifndef <xsl:value-of select="$name" /><xsl:value-of select="$objectid" />
    class <xsl:value-of select="$name" />Type : public Opaque&lt;30&gt; {};
    #endif
    </xsl:when>
    <xsl:when test="self::node()/Type='String'">
    #ifndef <xsl:value-of select="$name" /><xsl:value-of select="$objectid" />
    class <xsl:value-of select="$name" />Type : public PreallocString&lt;30&gt; {};
    #endif
    </xsl:when>
    <xsl:when test="self::node()/Type='Time'">
    #ifndef <xsl:value-of select="$name" /><xsl:value-of select="$objectid" />
    class <xsl:value-of select="$name" />Type : public PreallocString&lt;30&gt; {};
    #endif
    </xsl:when>
    </xsl:choose>
</xsl:for-each>

/* \brief Class for object <xsl:value-of select="ObjectID"/> - <xsl:value-of select="Name"/><xsl:call-template name="substring"><xsl:with-param name="text" select="concat(normalize-space(self::node()/Description1),normalize-space(self::node()/Description2))" /></xsl:call-template>
 */
class instance : public Lwm2mObjectInstance {
public:
<xsl:for-each select="Resources/Item">
    <xsl:variable name="resid" select="self::node()/@ID" />
    <xsl:variable name="name"><xsl:value-of select="fun:getName(Name, $objectid, $resid)" /></xsl:variable>
    <xsl:if test="self::node()/Mandatory='Optional'">
    // Optional resource</xsl:if>
    // <xsl:value-of select="$resid" /> - <xsl:value-of select="Description" />
<xsl:choose>
<xsl:when test="self::node()/Operations='E'">
    Executable <xsl:value-of select="$name" />;
</xsl:when>
<xsl:otherwise>
    <xsl:choose>
    <xsl:when test="self::node()/Type='Boolean'">
    bool <xsl:value-of select="$name" />;
    </xsl:when>
    <xsl:when test="self::node()/Type='Integer'">
    int <xsl:value-of select="$name" />;
    </xsl:when>
    <xsl:when test="self::node()/Type='Float'">
    float <xsl:value-of select="$name" />;
    </xsl:when>
    <xsl:when test="self::node()/Type='Opaque'">
    <xsl:value-of select="concat($newline,'    ')" />
    <xsl:value-of select="$name" />Type <xsl:value-of select="$name" />;
    </xsl:when>
    <xsl:when test="self::node()/Type='Objlnk'">
    // Objlnk resources are not supported yet - <xsl:value-of select="$name" />;
    </xsl:when>
    <xsl:when test="self::node()/Type='String'">
    <xsl:value-of select="concat($newline,'    ')" />
    <xsl:value-of select="$name" />Type <xsl:value-of select="$name" />;
    </xsl:when>
    <xsl:when test="self::node()/Type='Time'">
    <xsl:value-of select="concat($newline,'    ')" />
    <xsl:value-of select="$name" />Type <xsl:value-of select="$name" />; // Time
    </xsl:when>
    <xsl:otherwise>
        <xsl:message terminate="yes">Type not known: <xsl:apply-templates select="self::node()" mode="message"/></xsl:message>
    </xsl:otherwise>
    </xsl:choose>
</xsl:otherwise>
</xsl:choose>
</xsl:for-each>
};

enum class RESID {
    <xsl:for-each select="Resources/Item">
        <xsl:variable name="resid" select="self::node()/@ID" />
        <xsl:variable name="name"><xsl:value-of select="fun:getName(Name, $objectid, $resid)" /></xsl:variable>
        <xsl:value-of select="$name" /> = <xsl:value-of select="$resid" />,
    </xsl:for-each>
};

/* \brief Class for object <xsl:value-of select="ObjectID"/> - <xsl:value-of select="Name"/><xsl:call-template name="substring"><xsl:with-param name="text" select="concat(normalize-space(self::node()/Description1),normalize-space(self::node()/Description2))" /></xsl:call-template>
 */
class object : public Lwm2mObject&lt;<xsl:value-of select="ObjectID"/>, object, instance&gt; {
public:
<xsl:for-each select="Resources/Item">
    <xsl:variable name="resid" select="self::node()/@ID" />
    <xsl:variable name="name"><xsl:value-of select="fun:getName(Name, $objectid, $resid)" /></xsl:variable>
    <xsl:variable name="operations" select="fun:getOP(self::node()/Operations, $objectid, $resid)" />
    <xsl:if test="self::node()/Mandatory='Optional'">
    // Optional resource</xsl:if>
    // <xsl:value-of select="$resid" /> - <xsl:value-of select="Description" />
    <xsl:choose>
    <xsl:when test="$operations='O_RES_E'">
    Resource(<xsl:value-of select="$resid"/>, &amp;instance::<xsl:value-of select="$name" />) <xsl:value-of select="$name" />;
    </xsl:when>
    <xsl:when test="self::node()/Type='Objlnk'">
    // Objlnk resources are not supported yet - <xsl:value-of select="$name" />;
    </xsl:when>
    <xsl:otherwise>
    Resource(<xsl:value-of select="$resid"/>, &amp;instance::<xsl:value-of select="$name" />, <xsl:value-of select="$operations"/>) <xsl:value-of select="$name" />;
    </xsl:otherwise>
    </xsl:choose>
</xsl:for-each>
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id<xsl:value-of select="$objectid" />::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id<xsl:value-of select="$objectid" />::RESID c1) { return (uint16_t) c1 == c2; }
	</xsl:result-document>
	
    <xsl:copy>
      <xsl:apply-templates select="@*|node()"/>
    </xsl:copy>
  </xsl:if>
  </xsl:template>
</xsl:stylesheet>

