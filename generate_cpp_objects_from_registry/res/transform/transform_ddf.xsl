<xsl:stylesheet version="2.0"
                xmlns:xs="http://www.w3.org/2001/XMLSchema"
                xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                xmlns:functx="http://www.functx.com"
                exclude-result-prefixes="xs functx"
                >

<xsl:import href="functx-1.0-nodoc-2007-01.xsl"/>
<xsl:strip-space elements="*"/>
<xsl:output omit-xml-declaration="no" indent="yes" method="text" cdata-section-elements="description"/>

<xsl:template match="/DDFList">
<xsl:result-document method="text" href="known.h">#pragma once
// Automatically generated

<xsl:for-each select="Item">
<xsl:if test="ObjectID &gt; 0">#include "<xsl:value-of select="ObjectID"/>.h"
</xsl:if>
</xsl:for-each>

</xsl:result-document>
<xsl:result-document method="xml" href="html_list.htm">
  <style>
#lwm2mObjects tr:nth-child(even){background-color: #f2f2f2;}

#lwm2mObjects tr:hover {background-color: #ddd;}

#lwm2mObjects th {
    padding-top: 12px;
    padding-bottom: 12px;
    text-align: left;
    background-color: #ef5350;
    color: white;
}
  </style>
<table id="lwm2mObjects">
<thead>
    <tr>
      <th style="text-align:center">Object ID</th>
      <th style="text-align:left">Name</th>
      <th style="text-align:left">Description</th>
    </tr>
</thead>
<tbody>
    <xsl:for-each select="Item">
    <xsl:if test="ObjectID &gt; 0">
    <tr>
      <td><a href="{DDF}" title="{URN}"><xsl:value-of select="ObjectID"/></a></td>
      <td><xsl:value-of select="Name"/></td>
      <td><xsl:value-of select="Description"/></td>
    </tr>
    </xsl:if>
    </xsl:for-each>
</tbody>
</table>
</xsl:result-document>
</xsl:template>

</xsl:stylesheet>

