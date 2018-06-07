
<!--

 ********************************
 The FunctX XSLT Function Library
 ********************************

 Copyright (C) 2007 Datypic

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

 For more information on the FunctX XSLT library, contact contrib@functx.com.

 @version 1.0
 @see     http://www.xsltfunctions.com
--> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                xmlns:dxmlf="http://www.datypic.com/xmlf"
                xmlns:xs="http://www.w3.org/2001/XMLSchema"
                xmlns:fn="http://www.w3.org/2005/xpath-functions"
                xmlns:local="http://www.datypic.com/local"
                 xmlns:functx="http://www.functx.com"  
                exclude-result-prefixes="dxmlf xs" version="2.0">
 
<xsl:function name="functx:add-attributes" as="element()?" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="elements" as="element()*"/> 
  <xsl:param name="attrNames" as="xs:QName*"/> 
  <xsl:param name="attrValues" as="xs:anyAtomicType*"/> 
 
  <xsl:for-each select="$elements">
    <xsl:variable name="element" select="."/>
    <xsl:copy>
      <xsl:for-each select="$attrNames">
        <xsl:variable name="seq" select="position()"/>
        <xsl:if test="not($element/@*[node-name(.) = current()])">
          <xsl:attribute name="{.}"
                         namespace="{namespace-uri-from-QName(.)}"
                         select="$attrValues[$seq]"/>
        </xsl:if>
      </xsl:for-each>
      <xsl:copy-of select="@*|node()"/>
    </xsl:copy>
  </xsl:for-each>
 
</xsl:function>


<xsl:function name="functx:add-months" as="xs:date?" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="date" as="xs:anyAtomicType?"/> 
  <xsl:param name="months" as="xs:integer"/> 
 
  <xsl:sequence select=" 
   xs:date($date) + functx:yearMonthDuration(0,$months)
 "/>
   
</xsl:function>


<xsl:function name="functx:add-or-update-attributes" as="element()?" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="elements" as="element()*"/> 
  <xsl:param name="attrNames" as="xs:QName*"/> 
  <xsl:param name="attrValues" as="xs:anyAtomicType*"/> 
 
  <xsl:for-each select="$elements">
    <xsl:copy>
      <xsl:for-each select="$attrNames">
        <xsl:variable name="seq" select="position()"/>
        <xsl:attribute name="{.}"
                       namespace="{namespace-uri-from-QName(.)}"
                       select="$attrValues[$seq]"/>
      </xsl:for-each>
      <xsl:copy-of select="@*[not(node-name(.) = $attrNames)]|node()"/>
    </xsl:copy>
  </xsl:for-each>
 
</xsl:function>


<xsl:function name="functx:all-whitespace" as="xs:boolean" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="arg" as="xs:string?"/> 
 
  <xsl:sequence select=" 
   normalize-space($arg) = ''
 "/>
   
</xsl:function>


<xsl:function name="functx:are-distinct-values" as="xs:boolean" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="seq" as="xs:anyAtomicType*"/> 
 
  <xsl:sequence select=" 
   count(distinct-values($seq)) = count($seq)
 "/>
   
</xsl:function>


<xsl:function name="functx:atomic-type" as="xs:string*" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="values" as="xs:anyAtomicType*"/> 
 
  <xsl:sequence select=" 
 for $val in $values
 return
 (if ($val instance of xs:untypedAtomic) then 'xs:untypedAtomic'
 else if ($val instance of xs:anyURI) then 'xs:anyURI'
 else if ($val instance of xs:string) then 'xs:string'
 else if ($val instance of xs:QName) then 'xs:QName'
 else if ($val instance of xs:boolean) then 'xs:boolean'
 else if ($val instance of xs:base64Binary) then 'xs:base64Binary'
 else if ($val instance of xs:hexBinary) then 'xs:hexBinary'
 else if ($val instance of xs:integer) then 'xs:integer'
 else if ($val instance of xs:decimal) then 'xs:decimal'
 else if ($val instance of xs:float) then 'xs:float'
 else if ($val instance of xs:double) then 'xs:double'
 else if ($val instance of xs:date) then 'xs:date'
 else if ($val instance of xs:time) then 'xs:time'
 else if ($val instance of xs:dateTime) then 'xs:dateTime'
 else if ($val instance of xs:dayTimeDuration)
         then 'xs:dayTimeDuration'
 else if ($val instance of xs:yearMonthDuration)
         then 'xs:yearMonthDuration'
 else if ($val instance of xs:duration) then 'xs:duration'
 else if ($val instance of xs:gMonth) then 'xs:gMonth'
 else if ($val instance of xs:gYear) then 'xs:gYear'
 else if ($val instance of xs:gYearMonth) then 'xs:gYearMonth'
 else if ($val instance of xs:gDay) then 'xs:gDay'
 else if ($val instance of xs:gMonthDay) then 'xs:gMonthDay'
 else 'unknown')
 "/>
   
</xsl:function>


<xsl:function name="functx:avg-empty-is-zero" as="xs:double" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="values" as="xs:anyAtomicType*"/> 
  <xsl:param name="allNodes" as="node()*"/> 
 
  <xsl:sequence select=" 
   if (empty($allNodes))
   then 0
   else sum($values[string(.) != '']) div count($allNodes)
 "/>
   
</xsl:function>


<xsl:function name="functx:between-exclusive" as="xs:boolean" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="value" as="xs:anyAtomicType?"/> 
  <xsl:param name="minValue" as="xs:anyAtomicType"/> 
  <xsl:param name="maxValue" as="xs:anyAtomicType"/> 
 
  <xsl:sequence select=" 
   $value > $minValue and $value &lt; $maxValue
 "/>
   
</xsl:function>


<xsl:function name="functx:between-inclusive" as="xs:boolean" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="value" as="xs:anyAtomicType?"/> 
  <xsl:param name="minValue" as="xs:anyAtomicType"/> 
  <xsl:param name="maxValue" as="xs:anyAtomicType"/> 
 
  <xsl:sequence select=" 
   $value >= $minValue and $value &lt;= $maxValue
 "/>
   
</xsl:function>


<xsl:function name="functx:camel-case-to-words" as="xs:string" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="arg" as="xs:string?"/> 
  <xsl:param name="delim" as="xs:string"/> 
 
  <xsl:sequence select=" 
   concat(substring($arg,1,1),
             replace(substring($arg,2),'(\p{Lu})',
                        concat($delim, '$1')))
 "/>
   
</xsl:function>


<xsl:function name="functx:capitalize-first" as="xs:string?" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="arg" as="xs:string?"/> 
 
  <xsl:sequence select=" 
   concat(upper-case(substring($arg,1,1)),
             substring($arg,2))
 "/>
   
</xsl:function>


<xsl:function name="functx:change-element-names-deep" as="node()*" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="nodes" as="node()*"/> 
  <xsl:param name="oldNames" as="xs:QName*"/> 
  <xsl:param name="newNames" as="xs:QName*"/> 
 
  <xsl:if test="count($oldNames) != count($newNames)">
    <xsl:sequence select="error(
         xs:QName('functx:Different_number_of_names'))"/>
  </xsl:if>
  <xsl:for-each select="$nodes">
    <xsl:variable name="node" select="."/>
    <xsl:choose>
      <xsl:when test="$node instance of element()">
        <xsl:variable name="theName"
                      select="functx:if-empty
                    ($newNames[index-of($oldNames, node-name($node))],
                     node-name($node))"/>
        <xsl:element name="{$theName}"
                     namespace="{namespace-uri-from-QName($theName)}" >
           <xsl:sequence select="($node/@*,
                  functx:change-element-names-deep($node/node(),
                                           $oldNames, $newNames))"/>
        </xsl:element>
      </xsl:when>
      <xsl:when test="$node instance of document-node()">
        <xsl:document>
           <xsl:sequence select="functx:change-element-names-deep(
                $node/node(), $oldNames, $newNames)"/>
        </xsl:document>
      </xsl:when>
      <xsl:otherwise>
        <xsl:sequence select="$node"/>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:for-each>
 
</xsl:function>


<xsl:function name="functx:change-element-ns-deep" as="node()*" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="nodes" as="node()*"/> 
  <xsl:param name="newns" as="xs:string"/> 
  <xsl:param name="prefix" as="xs:string"/> 
 
  <xsl:for-each select="$nodes">
    <xsl:variable name="node" select="."/>
    <xsl:choose>
      <xsl:when test="$node instance of element()">
        <xsl:element name="{concat($prefix,
                                    if ($prefix = '')
                                    then ''
                                    else ':',
                                    local-name($node))}"
                     namespace="{$newns}">
          <xsl:sequence select="($node/@*,
                functx:change-element-ns-deep($node/node(),
                                           $newns, $prefix))"/>
        </xsl:element>
      </xsl:when>
      <xsl:when test="$node instance of document-node()">
        <xsl:document>
          <xsl:sequence select="functx:change-element-ns-deep(
                $node/node(), $newns, $prefix)"/>
        </xsl:document>
      </xsl:when>
      <xsl:otherwise>
        <xsl:sequence select="$node"/>
      </xsl:otherwise>
   </xsl:choose>
  </xsl:for-each>
 
</xsl:function>


<xsl:function name="functx:change-element-ns" as="element()?" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="elements" as="element()*"/> 
  <xsl:param name="newns" as="xs:string"/> 
  <xsl:param name="prefix" as="xs:string"/> 
 
   <xsl:for-each select="$elements">
     <xsl:variable name="element" select="."/>
     <xsl:element name="{concat($prefix,
                                    if ($prefix = '')
                                    then ''
                                    else ':',
                                    local-name($element))}"
                     namespace="{$newns}">
       <xsl:sequence select="$element/@*, $element/node()"/>
     </xsl:element>
   </xsl:for-each>
 
</xsl:function>


<xsl:function name="functx:chars" as="xs:string*" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="arg" as="xs:string?"/> 
 
  <xsl:sequence select=" 
   for $ch in string-to-codepoints($arg)
   return codepoints-to-string($ch)
 "/>
   
</xsl:function>


<xsl:function name="functx:contains-any-of" as="xs:boolean" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="arg" as="xs:string?"/> 
  <xsl:param name="searchStrings" as="xs:string*"/> 
 
  <xsl:sequence select=" 
   some $searchString in $searchStrings
   satisfies contains($arg,$searchString)
 "/>
   
</xsl:function>


<xsl:function name="functx:contains-case-insensitive" as="xs:boolean?" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="arg" as="xs:string?"/> 
  <xsl:param name="substring" as="xs:string"/> 
 
  <xsl:sequence select=" 
   contains(upper-case($arg), upper-case($substring))
 "/>
   
</xsl:function>


<xsl:function name="functx:contains-word" as="xs:boolean" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="arg" as="xs:string?"/> 
  <xsl:param name="word" as="xs:string"/> 
 
  <xsl:sequence select=" 
   matches(upper-case($arg),
           concat('^(.*\W)?',
                     upper-case(functx:escape-for-regex($word)),
                     '(\W.*)?$'))
 "/>
   
</xsl:function>


<xsl:function name="functx:copy-attributes" as="element()" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="copyTo" as="element()"/> 
  <xsl:param name="copyFrom" as="element()"/> 
 
  <xsl:element name="{node-name($copyTo)}">
    <xsl:sequence select="
       ($copyTo/@*[not(node-name(.) = $copyFrom/@*/node-name(.))],
        $copyFrom/@*,
        $copyTo/node())"/>
  </xsl:element>
 
</xsl:function>


<xsl:function name="functx:date" as="xs:date" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="year" as="xs:anyAtomicType"/> 
  <xsl:param name="month" as="xs:anyAtomicType"/> 
  <xsl:param name="day" as="xs:anyAtomicType"/> 
 
  <xsl:sequence select=" 
   xs:date(
     concat(
       functx:pad-integer-to-length(xs:integer($year),4),'-',
       functx:pad-integer-to-length(xs:integer($month),2),'-',
       functx:pad-integer-to-length(xs:integer($day),2)))
 "/>
   
</xsl:function>


<xsl:function name="functx:dateTime" as="xs:dateTime" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="year" as="xs:anyAtomicType"/> 
  <xsl:param name="month" as="xs:anyAtomicType"/> 
  <xsl:param name="day" as="xs:anyAtomicType"/> 
  <xsl:param name="hour" as="xs:anyAtomicType"/> 
  <xsl:param name="minute" as="xs:anyAtomicType"/> 
  <xsl:param name="second" as="xs:anyAtomicType"/> 
 
  <xsl:sequence select=" 
   xs:dateTime(
     concat(functx:date($year,$month,$day),'T',
             functx:time($hour,$minute,$second)))
 "/>
   
</xsl:function>


<xsl:function name="functx:day-in-year" as="xs:integer?" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="date" as="xs:anyAtomicType?"/> 
 
  <xsl:sequence select=" 
  days-from-duration(
      xs:date($date) - functx:first-day-of-year($date)) + 1
 "/>
   
</xsl:function>


<xsl:function name="functx:day-of-week-abbrev-en" as="xs:string?" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="date" as="xs:anyAtomicType?"/> 
 
  <xsl:sequence select=" 
   ('Sun', 'Mon', 'Tues', 'Wed', 'Thurs', 'Fri', 'Sat')
   [functx:day-of-week($date) + 1]
 "/>
   
</xsl:function>


<xsl:function name="functx:day-of-week-name-en" as="xs:string?" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="date" as="xs:anyAtomicType?"/> 
 
  <xsl:sequence select=" 
   ('Sunday', 'Monday', 'Tuesday', 'Wednesday',
    'Thursday', 'Friday', 'Saturday')
      [functx:day-of-week($date) + 1]
 "/>
   
</xsl:function>


<xsl:function name="functx:day-of-week" as="xs:integer?" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="date" as="xs:anyAtomicType?"/> 
 
  <xsl:sequence select=" 
  if (empty($date))
  then ()
  else xs:integer((xs:date($date) - xs:date('1901-01-06'))
          div xs:dayTimeDuration('P1D')) mod 7
 "/>
   
</xsl:function>


<xsl:function name="functx:dayTimeDuration" as="xs:dayTimeDuration" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="days" as="xs:decimal?"/> 
  <xsl:param name="hours" as="xs:decimal?"/> 
  <xsl:param name="minutes" as="xs:decimal?"/> 
  <xsl:param name="seconds" as="xs:decimal?"/> 
 
  <xsl:sequence select=" 
    (xs:dayTimeDuration('P1D') * functx:if-empty($days,0)) +
    (xs:dayTimeDuration('PT1H') * functx:if-empty($hours,0)) +
    (xs:dayTimeDuration('PT1M') * functx:if-empty($minutes,0)) +
    (xs:dayTimeDuration('PT1S') * functx:if-empty($seconds,0))
 "/>
   
</xsl:function>


<xsl:function name="functx:days-in-month" as="xs:integer?" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="date" as="xs:anyAtomicType?"/> 
 
  <xsl:sequence select=" 
   if (month-from-date(xs:date($date)) = 2 and
       functx:is-leap-year($date))
   then 29
   else
   (31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31)
    [month-from-date(xs:date($date))]
 "/>
   
</xsl:function>


<xsl:function name="functx:depth-of-node" as="xs:integer" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="node" as="node()?"/> 
 
  <xsl:sequence select=" 
   count($node/ancestor-or-self::node())
 "/>
   
</xsl:function>


<xsl:function name="functx:distinct-attribute-names" as="xs:string*" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="nodes" as="node()*"/> 
 
  <xsl:sequence select=" 
   distinct-values($nodes//@*/name(.))
 "/>
   
</xsl:function>


<xsl:function name="functx:distinct-deep" as="node()*" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="nodes" as="node()*"/> 
 
  <xsl:sequence select=" 
    for $seq in (1 to count($nodes))
    return $nodes[$seq][not(functx:is-node-in-sequence-deep-equal(
                          .,$nodes[position() &lt; $seq]))]
 "/>
   
</xsl:function>


<xsl:function name="functx:distinct-element-names" as="xs:string*" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="nodes" as="node()*"/> 
 
  <xsl:sequence select=" 
   distinct-values($nodes/descendant-or-self::*/name(.))
 "/>
   
</xsl:function>


<xsl:function name="functx:distinct-element-paths" as="xs:string*" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="nodes" as="node()*"/> 
 
  <xsl:sequence select=" 
   distinct-values(functx:path-to-node($nodes/descendant-or-self::*))
 "/>
   
</xsl:function>


<xsl:function name="functx:distinct-nodes" as="node()*" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="nodes" as="node()*"/> 
 
  <xsl:sequence select=" 
    for $seq in (1 to count($nodes))
    return $nodes[$seq][not(functx:is-node-in-sequence(
                                .,$nodes[position() &lt; $seq]))]
 "/>
   
</xsl:function>


<xsl:function name="functx:duration-from-timezone" as="xs:dayTimeDuration" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="timezone" as="xs:string"/> 
 
  <xsl:sequence select=" 
   xs:dayTimeDuration(
     if (not(matches($timezone,'Z|[\+\-]\d{2}:\d{2}')))
     then error(xs:QName('functx:Invalid_Timezone_Value'))
     else if ($timezone = 'Z')
     then 'PT0S'
     else replace($timezone,'\+?(\d{2}):\d{2}','PT$1H')
        )
 "/>
   
</xsl:function>


<xsl:function name="functx:dynamic-path" as="item()*" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="parent" as="node()"/> 
  <xsl:param name="path" as="xs:string"/> 
 
  <xsl:variable name="nextStep"
        select="functx:substring-before-if-contains($path,'/')"/>
  <xsl:variable name="restOfSteps"
        select="substring-after($path,'/')"/>
  <xsl:for-each select="
    ($parent/*[functx:name-test(name(),$nextStep)],
     $parent/@*[functx:name-test(name(),
                              substring-after($nextStep,'@'))])">
    <xsl:variable name="child" select="."/>
    <xsl:sequence select="if ($restOfSteps)
         then functx:dynamic-path($child, $restOfSteps)
         else $child"/>
  </xsl:for-each>
 
</xsl:function>


<xsl:function name="functx:escape-for-regex" as="xs:string" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="arg" as="xs:string?"/> 
 
  <xsl:sequence select=" 
   replace($arg,
           '(\.|\[|\]|\\|\||\-|\^|\$|\?|\*|\+|\{|\}|\(|\))','\\$1')
 "/>
   
</xsl:function>


<xsl:function name="functx:exclusive-or" as="xs:boolean?" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="arg1" as="xs:boolean?"/> 
  <xsl:param name="arg2" as="xs:boolean?"/> 
 
  <xsl:sequence select=" 
   $arg1 != $arg2
 "/>
   
</xsl:function>


<xsl:function name="functx:first-day-of-month" as="xs:date?" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="date" as="xs:anyAtomicType?"/> 
 
  <xsl:sequence select=" 
   functx:date(year-from-date(xs:date($date)),
            month-from-date(xs:date($date)),
            1)
 "/>
   
</xsl:function>


<xsl:function name="functx:first-day-of-year" as="xs:date?" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="date" as="xs:anyAtomicType?"/> 
 
  <xsl:sequence select=" 
   functx:date(year-from-date(xs:date($date)), 1, 1)
 "/>
   
</xsl:function>


<xsl:function name="functx:first-node" as="node()?" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="nodes" as="node()*"/> 
 
  <xsl:sequence select=" 
   ($nodes/.)[1]
 "/>
   
</xsl:function>


<xsl:function name="functx:follows-not-descendant" as="xs:boolean" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="a" as="node()?"/> 
  <xsl:param name="b" as="node()?"/> 
 
  <xsl:sequence select=" 
   $a >> $b and empty($b intersect $a/ancestor::node())
 "/>
   
</xsl:function>


<xsl:function name="functx:format-as-title-en" as="xs:string*" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="titles" as="xs:string*"/> 
 
   <xsl:variable name="wordsToMoveToEnd"
                 select="('A', 'An', 'The')"/>
   <xsl:for-each select="$titles">
     <xsl:variable name="title" select="."/>
     <xsl:variable name="firstWord"
          select="functx:substring-before-match($title,'\W')"/>
     <xsl:sequence select="if ($firstWord = $wordsToMoveToEnd)
          then replace($title,'(.*?)\W(.*)', '$2, $1')
          else $title"/>
   </xsl:for-each>
 
</xsl:function>


<xsl:function name="functx:fragment-from-uri" as="xs:string?" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="uri" as="xs:string?"/> 
 
  <xsl:sequence select=" 
   substring-after($uri,'#')
 "/>
   
</xsl:function>


<xsl:function name="functx:has-element-only-content" as="xs:boolean" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="element" as="element()"/> 
 
  <xsl:sequence select=" 
   not($element/text()[normalize-space(.) != '']) and $element/*
 "/>
   
</xsl:function>


<xsl:function name="functx:has-empty-content" as="xs:boolean" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="element" as="element()"/> 
 
  <xsl:sequence select=" 
   not($element/node())
 "/>
   
</xsl:function>


<xsl:function name="functx:has-mixed-content" as="xs:boolean" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="element" as="element()"/> 
 
  <xsl:sequence select=" 
   $element/text()[normalize-space(.) != ''] and $element/*
 "/>
   
</xsl:function>


<xsl:function name="functx:has-simple-content" as="xs:boolean" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="element" as="element()"/> 
 
  <xsl:sequence select=" 
   $element/text() and not($element/*)
 "/>
   
</xsl:function>


<xsl:function name="functx:id-from-element" as="xs:string?" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="element" as="element()?"/> 
 
  <xsl:sequence select=" 
  data(($element/@*[id(.) is ..])[1])
 "/>
   
</xsl:function>


<xsl:function name="functx:id-untyped" as="element()*" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="node" as="node()*"/> 
  <xsl:param name="id" as="xs:anyAtomicType"/> 
 
  <xsl:sequence select=" 
  $node//*[@* = $id]
 "/>
   
</xsl:function>


<xsl:function name="functx:if-absent" as="item()*" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="arg" as="item()*"/> 
  <xsl:param name="value" as="item()*"/> 
 
  <xsl:sequence select=" 
    if (exists($arg))
    then $arg
    else $value
 "/>
   
</xsl:function>


<xsl:function name="functx:if-empty" as="item()*" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="arg" as="item()?"/> 
  <xsl:param name="value" as="item()*"/> 
 
  <xsl:sequence select=" 
  if (string($arg) != '')
  then data($arg)
  else $value
 "/>
   
</xsl:function>


<xsl:function name="functx:index-of-deep-equal-node" as="xs:integer*" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="nodes" as="node()*"/> 
  <xsl:param name="nodeToFind" as="node()"/> 
 
  <xsl:sequence select=" 
  for $seq in (1 to count($nodes))
  return $seq[deep-equal($nodes[$seq],$nodeToFind)]
 "/>
   
</xsl:function>


<xsl:function name="functx:index-of-match-first" as="xs:integer?" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="arg" as="xs:string?"/> 
  <xsl:param name="pattern" as="xs:string"/> 
 
  <xsl:sequence select=" 
  if (matches($arg,$pattern))
  then string-length(tokenize($arg, $pattern)[1]) + 1
  else ()
 "/>
   
</xsl:function>


<xsl:function name="functx:index-of-node" as="xs:integer*" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="nodes" as="node()*"/> 
  <xsl:param name="nodeToFind" as="node()"/> 
 
  <xsl:sequence select=" 
  for $seq in (1 to count($nodes))
  return $seq[$nodes[$seq] is $nodeToFind]
 "/>
   
</xsl:function>


<xsl:function name="functx:index-of-string-first" as="xs:integer?" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="arg" as="xs:string?"/> 
  <xsl:param name="substring" as="xs:string"/> 
 
  <xsl:sequence select=" 
  if (contains($arg, $substring))
  then string-length(substring-before($arg, $substring))+1
  else ()
 "/>
   
</xsl:function>


<xsl:function name="functx:index-of-string-last" as="xs:integer?" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="arg" as="xs:string?"/> 
  <xsl:param name="substring" as="xs:string"/> 
 
  <xsl:sequence select=" 
  functx:index-of-string($arg, $substring)[last()]
 "/>
   
</xsl:function>


<xsl:function name="functx:index-of-string" as="xs:integer*" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="arg" as="xs:string?"/> 
  <xsl:param name="substring" as="xs:string"/> 
 
  <xsl:sequence select=" 
  if (contains($arg, $substring))
  then (string-length(substring-before($arg, $substring))+1,
        for $other in
           functx:index-of-string(substring-after($arg, $substring),
                               $substring)
        return
          $other +
          string-length(substring-before($arg, $substring)) +
          string-length($substring))
  else ()
 "/>
   
</xsl:function>


<xsl:function name="functx:insert-string" as="xs:string" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="originalString" as="xs:string?"/> 
  <xsl:param name="stringToInsert" as="xs:string?"/> 
  <xsl:param name="pos" as="xs:integer"/> 
 
  <xsl:sequence select=" 
   concat(substring($originalString,1,$pos - 1),
             $stringToInsert,
             substring($originalString,$pos))
 "/>
   
</xsl:function>


<xsl:function name="functx:is-a-number" as="xs:boolean" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="value" as="xs:anyAtomicType?"/> 
 
  <xsl:sequence select=" 
   string(number($value)) != 'NaN'
 "/>
   
</xsl:function>


<xsl:function name="functx:is-absolute-uri" as="xs:boolean" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="uri" as="xs:string?"/> 
 
  <xsl:sequence select=" 
   matches($uri,'^[a-z]+:')
 "/>
   
</xsl:function>


<xsl:function name="functx:is-ancestor" as="xs:boolean" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="node1" as="node()"/> 
  <xsl:param name="node2" as="node()"/> 
 
  <xsl:sequence select=" 
   exists($node1 intersect $node2/ancestor::node())
 "/>
   
</xsl:function>


<xsl:function name="functx:is-descendant" as="xs:boolean" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="node1" as="node()"/> 
  <xsl:param name="node2" as="node()"/> 
 
  <xsl:sequence select=" 
   boolean($node2 intersect $node1/ancestor::node())
 "/>
   
</xsl:function>


<xsl:function name="functx:is-leap-year" as="xs:boolean" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="date" as="xs:anyAtomicType?"/> 
 
  <xsl:sequence select=" 
    for $year in xs:integer(substring(string($date),1,4))
    return ($year mod 4 = 0 and
            $year mod 100 != 0) or
            $year mod 400 = 0
 "/>
   
</xsl:function>


<xsl:function name="functx:is-node-among-descendants-deep-equal" as="xs:boolean" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="node" as="node()?"/> 
  <xsl:param name="seq" as="node()*"/> 
 
  <xsl:sequence select=" 
   some $nodeInSeq in $seq/descendant-or-self::*/(.|@*)
   satisfies deep-equal($nodeInSeq,$node)
 "/>
   
</xsl:function>


<xsl:function name="functx:is-node-among-descendants" as="xs:boolean" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="node" as="node()?"/> 
  <xsl:param name="seq" as="node()*"/> 
 
  <xsl:sequence select=" 
   some $nodeInSeq in $seq/descendant-or-self::*/(.|@*)
   satisfies $nodeInSeq is $node
 "/>
   
</xsl:function>


<xsl:function name="functx:is-node-in-sequence-deep-equal" as="xs:boolean" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="node" as="node()?"/> 
  <xsl:param name="seq" as="node()*"/> 
 
  <xsl:sequence select=" 
   some $nodeInSeq in $seq satisfies deep-equal($nodeInSeq,$node)
 "/>
   
</xsl:function>


<xsl:function name="functx:is-node-in-sequence" as="xs:boolean" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="node" as="node()?"/> 
  <xsl:param name="seq" as="node()*"/> 
 
  <xsl:sequence select=" 
   some $nodeInSeq in $seq satisfies $nodeInSeq is $node
 "/>
   
</xsl:function>


<xsl:function name="functx:is-value-in-sequence" as="xs:boolean" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="value" as="xs:anyAtomicType?"/> 
  <xsl:param name="seq" as="xs:anyAtomicType*"/> 
 
  <xsl:sequence select=" 
   $value = $seq
 "/>
   
</xsl:function>


<xsl:function name="functx:last-day-of-month" as="xs:date?" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="date" as="xs:anyAtomicType?"/> 
 
  <xsl:sequence select=" 
   functx:date(year-from-date(xs:date($date)),
            month-from-date(xs:date($date)),
            functx:days-in-month($date))
 "/>
   
</xsl:function>


<xsl:function name="functx:last-day-of-year" as="xs:date?" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="date" as="xs:anyAtomicType?"/> 
 
  <xsl:sequence select=" 
   functx:date(year-from-date(xs:date($date)), 12, 31)
 "/>
   
</xsl:function>


<xsl:function name="functx:last-node" as="node()?" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="nodes" as="node()*"/> 
 
  <xsl:sequence select=" 
   ($nodes/.)[last()]
 "/>
   
</xsl:function>


<xsl:function name="functx:leaf-elements" as="element()*" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="root" as="node()?"/> 
 
  <xsl:sequence select=" 
   $root/descendant-or-self::*[not(*)]
 "/>
   
</xsl:function>


<xsl:function name="functx:left-trim" as="xs:string" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="arg" as="xs:string?"/> 
 
  <xsl:sequence select=" 
   replace($arg,'^\s+','')
 "/>
   
</xsl:function>


<xsl:function name="functx:line-count" as="xs:integer" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="arg" as="xs:string?"/> 
 
  <xsl:sequence select=" 
   count(functx:lines($arg))
 "/>
   
</xsl:function>


<xsl:function name="functx:lines" as="xs:string*" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="arg" as="xs:string?"/> 
 
  <xsl:sequence select=" 
   tokenize($arg, '(\r\n?|\n\r?)')
 "/>
   
</xsl:function>


<xsl:function name="functx:max-depth" as="xs:integer?" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="root" as="node()?"/> 
 
  <xsl:sequence select=" 
   if ($root/*)
   then max($root/*/functx:max-depth(.)) + 1
   else 1
 "/>
   
</xsl:function>


<xsl:function name="functx:max-determine-type" as="xs:anyAtomicType?" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="seq" as="xs:anyAtomicType*"/> 
 
  <xsl:sequence select=" 
   if (every $value in $seq satisfies ($value castable as xs:double))
   then max(for $value in $seq return xs:double($value))
   else max(for $value in $seq return xs:string($value))
 "/>
   
</xsl:function>


<xsl:function name="functx:max-line-length" as="xs:integer" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="arg" as="xs:string?"/> 
 
  <xsl:sequence select=" 
   max(
     for $line in functx:lines($arg)
     return string-length($line))
 "/>
   
</xsl:function>


<xsl:function name="functx:max-node" as="node()*" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="nodes" as="node()*"/> 
 
  <xsl:sequence select=" 
   $nodes[. = max($nodes)]
 "/>
   
</xsl:function>


<xsl:function name="functx:max-string" as="xs:string?" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="strings" as="xs:anyAtomicType*"/> 
 
  <xsl:sequence select=" 
   max(for $string in $strings return string($string))
 "/>
   
</xsl:function>


<xsl:function name="functx:min-determine-type" as="xs:anyAtomicType?" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="seq" as="xs:anyAtomicType*"/> 
 
  <xsl:sequence select=" 
   if (every $value in $seq satisfies ($value castable as xs:double))
   then min(for $value in $seq return xs:double($value))
   else min(for $value in $seq return xs:string($value))
 "/>
   
</xsl:function>


<xsl:function name="functx:min-node" as="node()*" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="nodes" as="node()*"/> 
 
  <xsl:sequence select=" 
   $nodes[. = min($nodes)]
 "/>
   
</xsl:function>


<xsl:function name="functx:min-non-empty-string" as="xs:string?" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="strings" as="xs:string*"/> 
 
  <xsl:sequence select=" 
   min($strings[. != ''])
 "/>
   
</xsl:function>


<xsl:function name="functx:min-string" as="xs:string?" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="strings" as="xs:anyAtomicType*"/> 
 
  <xsl:sequence select=" 
   min(for $string in $strings return string($string))
 "/>
   
</xsl:function>


<xsl:function name="functx:mmddyyyy-to-date" as="xs:date?" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="dateString" as="xs:string?"/> 
 
  <xsl:sequence select=" 
   if (empty($dateString))
   then ()
   else if (not(matches($dateString,
                        '^\D*(\d{2})\D*(\d{2})\D*(\d{4})\D*$')))
   then error(xs:QName('functx:Invalid_Date_Format'))
   else xs:date(replace($dateString,
                        '^\D*(\d{2})\D*(\d{2})\D*(\d{4})\D*$',
                        '$3-$1-$2'))
 "/>
   
</xsl:function>


<xsl:function name="functx:month-abbrev-en" as="xs:string?" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="date" as="xs:anyAtomicType?"/> 
 
  <xsl:sequence select=" 
   ('Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun',
    'Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec')
    [month-from-date(xs:date($date))]
 "/>
   
</xsl:function>


<xsl:function name="functx:month-name-en" as="xs:string?" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="date" as="xs:anyAtomicType?"/> 
 
  <xsl:sequence select=" 
   ('January', 'February', 'March', 'April', 'May', 'June',
    'July', 'August', 'September', 'October', 'November', 'December')
   [month-from-date(xs:date($date))]
 "/>
   
</xsl:function>


<xsl:function name="functx:name-test" as="xs:boolean" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="testname" as="xs:string?"/> 
  <xsl:param name="names" as="xs:string*"/> 
 
  <xsl:sequence select=" 
$testname = $names
or
$names = '*'
or
functx:substring-after-if-contains($testname,':') =
   (for $name in $names
   return substring-after($name,'*:'))
or
substring-before($testname,':') =
   (for $name in $names[contains(.,':*')]
   return substring-before($name,':*'))
 "/>
   
</xsl:function>


<xsl:function name="functx:namespaces-in-use" as="xs:anyURI*" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="root" as="node()?"/> 
 
  <xsl:sequence select=" 
   distinct-values(
      $root/descendant-or-self::*/(.|@*)/namespace-uri(.))
 "/>
   
</xsl:function>


<xsl:function name="functx:next-day" as="xs:date?" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="date" as="xs:anyAtomicType?"/> 
 
  <xsl:sequence select=" 
   xs:date($date) + xs:dayTimeDuration('P1D')
 "/>
   
</xsl:function>


<xsl:function name="functx:node-kind" as="xs:string*" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="nodes" as="node()*"/> 
 
  <xsl:sequence select=" 
 for $node in $nodes
 return
 if ($node instance of element()) then 'element'
 else if ($node instance of attribute()) then 'attribute'
 else if ($node instance of text()) then 'text'
 else if ($node instance of document-node()) then 'document-node'
 else if ($node instance of comment()) then 'comment'
 else if ($node instance of processing-instruction())
         then 'processing-instruction'
 else 'unknown'
 "/>
   
</xsl:function>


<xsl:function name="functx:non-distinct-values" as="xs:anyAtomicType*" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="seq" as="xs:anyAtomicType*"/> 
 
  <xsl:sequence select=" 
   for $val in distinct-values($seq)
   return $val[count($seq[. = $val]) > 1]
 "/>
   
</xsl:function>


<xsl:function name="functx:number-of-matches" as="xs:integer" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="arg" as="xs:string?"/> 
  <xsl:param name="pattern" as="xs:string"/> 
 
  <xsl:sequence select=" 
   count(tokenize($arg,$pattern)) - 1
 "/>
   
</xsl:function>


<xsl:function name="functx:open-ref-document" as="document-node()" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="refNode" as="node()"/> 
 
  <xsl:sequence select=" 
   if (base-uri($refNode))
   then doc(resolve-uri($refNode, base-uri($refNode)))
   else doc(resolve-uri($refNode))
 "/>
   
</xsl:function>


<xsl:function name="functx:ordinal-number-en" as="xs:string" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="num" as="xs:integer?"/> 
 
  <xsl:sequence select=" 
   concat(xs:string($num),
         if (matches(xs:string($num),'[04-9]$|1[1-3]$')) then 'th'
         else if (ends-with(xs:string($num),'1')) then 'st'
         else if (ends-with(xs:string($num),'2')) then 'nd'
         else if (ends-with(xs:string($num),'3')) then 'rd'
         else '')
 "/>
   
</xsl:function>


<xsl:function name="functx:pad-integer-to-length" as="xs:string" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="integerToPad" as="xs:anyAtomicType?"/> 
  <xsl:param name="length" as="xs:integer"/> 
 
  <xsl:sequence select=" 
   if ($length &lt; string-length(string($integerToPad)))
   then error(xs:QName('functx:Integer_Longer_Than_Length'))
   else concat
         (functx:repeat-string(
            '0',$length - string-length(string($integerToPad))),
          string($integerToPad))
 "/>
   
</xsl:function>


<xsl:function name="functx:pad-string-to-length" as="xs:string" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="stringToPad" as="xs:string?"/> 
  <xsl:param name="padChar" as="xs:string"/> 
  <xsl:param name="length" as="xs:integer"/> 
 
  <xsl:sequence select=" 
   substring(
     string-join (
       ($stringToPad, for $i in (1 to $length) return $padChar)
       ,'')
    ,1,$length)
 "/>
   
</xsl:function>


<xsl:function name="functx:path-to-node-with-pos" as="xs:string" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="node" as="node()?"/> 
 
 <xsl:variable name="names" as="xs:string*">
   <xsl:for-each select="$node/ancestor-or-self::*">
     <xsl:variable name="ancestor" select="."/>
     <xsl:variable name="sibsOfSameName"
           select="$ancestor/../*[name() = name($ancestor)]"/>
     <xsl:sequence select="concat(name($ancestor),
         if (count($sibsOfSameName) &lt;= 1)
         then ''
         else concat(
        '[',functx:index-of-node($sibsOfSameName,$ancestor),']'))"/>
   </xsl:for-each>
 </xsl:variable>
 <xsl:sequence select="string-join($names,'/')"/>
 
</xsl:function>


<xsl:function name="functx:path-to-node" as="xs:string*" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="nodes" as="node()*"/> 
 
  <xsl:sequence select=" 
$nodes/string-join(ancestor-or-self::*/name(.), '/')
 "/>
   
</xsl:function>


<xsl:function name="functx:precedes-not-ancestor" as="xs:boolean" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="a" as="node()?"/> 
  <xsl:param name="b" as="node()?"/> 
 
  <xsl:sequence select=" 
   $a &lt;&lt; $b and empty($a intersect $b/ancestor::node())
 "/>
   
</xsl:function>


<xsl:function name="functx:previous-day" as="xs:date?" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="date" as="xs:anyAtomicType?"/> 
 
  <xsl:sequence select=" 
   xs:date($date) - xs:dayTimeDuration('P1D')
 "/>
   
</xsl:function>


<xsl:function name="functx:remove-attributes-deep" as="node()*" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="nodes" as="node()*"/> 
  <xsl:param name="names" as="xs:string*"/> 
 
   <xsl:for-each select="$nodes">
     <xsl:choose>
       <xsl:when test=". instance of element()">
         <xsl:element name="{node-name(.)}">
           <xsl:sequence select="
              (@*[not(functx:name-test(name(),$names))],
               functx:remove-attributes-deep(node(), $names))"/>
         </xsl:element>
       </xsl:when>
       <xsl:when test=". instance of document-node()">
         <xsl:document>
           <xsl:sequence select="
                functx:remove-attributes-deep(node(), $names)"/>
         </xsl:document>
       </xsl:when>
       <xsl:otherwise>
         <xsl:sequence select="."/>
       </xsl:otherwise>
     </xsl:choose>
   </xsl:for-each>
 
</xsl:function>


<xsl:function name="functx:remove-attributes" as="element()" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="elements" as="element()*"/> 
  <xsl:param name="names" as="xs:string*"/> 
 
   <xsl:for-each select="$elements">
     <xsl:element name="{node-name(.)}">
       <xsl:sequence
         select="(@*[not(functx:name-test(name(),$names))],
                 node())"/>
     </xsl:element>
   </xsl:for-each>
 
</xsl:function>


<xsl:function name="functx:remove-elements-deep" as="node()*" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="nodes" as="node()*"/> 
  <xsl:param name="names" as="xs:string*"/> 
 
   <xsl:for-each select="$nodes">
     <xsl:choose>
       <xsl:when test=". instance of element()">
         <xsl:if test="not(functx:name-test(name(),$names))">
           <xsl:element name="{node-name(.)}">
             <xsl:sequence select="@*,
                  functx:remove-elements-deep(node(), $names)"/>
           </xsl:element>
         </xsl:if>
       </xsl:when>
       <xsl:when test=". instance of document-node()">
         <xsl:document>
             <xsl:sequence select="
                  functx:remove-elements-deep(node(), $names)"/>
         </xsl:document>
       </xsl:when>
       <xsl:otherwise>
         <xsl:sequence select="."/>
       </xsl:otherwise>
     </xsl:choose>
   </xsl:for-each>
 
</xsl:function>


<xsl:function name="functx:remove-elements-not-contents" as="node()*" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="nodes" as="node()*"/> 
  <xsl:param name="names" as="xs:string*"/> 
 
   <xsl:for-each select="$nodes">
     <xsl:choose>
       <xsl:when test=". instance of element()">
         <xsl:choose>
           <xsl:when test="functx:name-test(name(),$names)">
             <xsl:sequence select="
                 functx:remove-elements-not-contents(node(), $names)"/>
           </xsl:when>
           <xsl:otherwise>
             <xsl:element name="{node-name(.)}">
               <xsl:sequence select="@*,
                 functx:remove-elements-not-contents(node(),$names)"/>
             </xsl:element>
           </xsl:otherwise>
         </xsl:choose>
       </xsl:when>
       <xsl:when test=". instance of document-node()">
         <xsl:document>
             <xsl:sequence select="
                 functx:remove-elements-not-contents(node(), $names)"/>
         </xsl:document>
       </xsl:when>
       <xsl:otherwise>
         <xsl:sequence select="."/>
       </xsl:otherwise>
     </xsl:choose>
   </xsl:for-each>
 
</xsl:function>


<xsl:function name="functx:remove-elements" as="element()*" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="elements" as="element()*"/> 
  <xsl:param name="names" as="xs:string*"/> 
 
   <xsl:for-each select="$elements">
     <xsl:element name="{node-name(.)}">
       <xsl:sequence select="(@*,
      node()[not(functx:name-test(name(),$names))])"/>
     </xsl:element>
   </xsl:for-each>
 
</xsl:function>


<xsl:function name="functx:repeat-string" as="xs:string" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="stringToRepeat" as="xs:string?"/> 
  <xsl:param name="count" as="xs:integer"/> 
 
  <xsl:sequence select=" 
   string-join((for $i in 1 to $count return $stringToRepeat),
                        '')
 "/>
   
</xsl:function>


<xsl:function name="functx:replace-beginning" as="xs:string" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="arg" as="xs:string?"/> 
  <xsl:param name="pattern" as="xs:string"/> 
  <xsl:param name="replacement" as="xs:string"/> 
 
  <xsl:sequence select=" 
   replace($arg, concat('^.*?', $pattern), $replacement)
 "/>
   
</xsl:function>


<xsl:function name="functx:replace-element-values" as="element()*" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="elements" as="element()*"/> 
  <xsl:param name="values" as="xs:anyAtomicType*"/> 
 
   <xsl:for-each select="$elements">
     <xsl:variable name="seq" select="position()"/>
     <xsl:element name="{node-name(.)}">
       <xsl:sequence select="@*, $values[$seq]"/>
     </xsl:element>
   </xsl:for-each>
 
</xsl:function>


<xsl:function name="functx:replace-first" as="xs:string" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="arg" as="xs:string?"/> 
  <xsl:param name="pattern" as="xs:string"/> 
  <xsl:param name="replacement" as="xs:string"/> 
 
  <xsl:sequence select=" 
   replace($arg, concat('(^.*?)', $pattern),
             concat('$1',$replacement))
 "/>
   
</xsl:function>


<xsl:function name="functx:replace-multi" as="xs:string?" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="arg" as="xs:string?"/> 
  <xsl:param name="changeFrom" as="xs:string*"/> 
  <xsl:param name="changeTo" as="xs:string*"/> 
 
  <xsl:sequence select=" 
   if (count($changeFrom) > 0)
   then functx:replace-multi(
          replace($arg, $changeFrom[1],
                     functx:if-absent($changeTo[1],'')),
          $changeFrom[position() > 1],
          $changeTo[position() > 1])
   else $arg
 "/>
   
</xsl:function>


<xsl:function name="functx:reverse-string" as="xs:string" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="arg" as="xs:string?"/> 
 
  <xsl:sequence select=" 
   codepoints-to-string(reverse(string-to-codepoints($arg)))
 "/>
   
</xsl:function>


<xsl:function name="functx:right-trim" as="xs:string" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="arg" as="xs:string?"/> 
 
  <xsl:sequence select=" 
   replace($arg,'\s+$','')
 "/>
   
</xsl:function>


<xsl:function name="functx:scheme-from-uri" as="xs:string?" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="uri" as="xs:string?"/> 
 
  <xsl:sequence select=" 
   substring-before($uri,':')
 "/>
   
</xsl:function>


<xsl:function name="functx:sequence-deep-equal" as="xs:boolean" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="seq1" as="item()*"/> 
  <xsl:param name="seq2" as="item()*"/> 
 
  <xsl:sequence select=" 
  every $i in 1 to max((count($seq1),count($seq2)))
  satisfies deep-equal($seq1[$i],$seq2[$i])
 "/>
   
</xsl:function>


<xsl:function name="functx:sequence-node-equal-any-order" as="xs:boolean" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="seq1" as="node()*"/> 
  <xsl:param name="seq2" as="node()*"/> 
 
  <xsl:sequence select=" 
  not( ($seq1 except $seq2, $seq2 except $seq1))
 "/>
   
</xsl:function>


<xsl:function name="functx:sequence-node-equal" as="xs:boolean" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="seq1" as="node()*"/> 
  <xsl:param name="seq2" as="node()*"/> 
 
  <xsl:sequence select=" 
  every $i in 1 to max((count($seq1),count($seq2)))
  satisfies $seq1[$i] is $seq2[$i]
 "/>
   
</xsl:function>


<xsl:function name="functx:sequence-type" as="xs:string" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="items" as="item()*"/> 
 
  <xsl:sequence select=" 
concat(
  if (empty($items))
  then 'empty-sequence()'
  else if (every $val in $items
           satisfies $val instance of xs:anyAtomicType)
  then if (count(distinct-values(functx:atomic-type($items)))
           > 1)
  then 'xs:anyAtomicType'
  else functx:atomic-type($items[1])
  else if (some $val in $items
           satisfies $val instance of xs:anyAtomicType)
  then 'item()'
  else if (count(distinct-values(functx:node-kind($items))) > 1)
  then 'node()'
  else concat(functx:node-kind($items[1]),'()')
  ,
  if (count($items) > 1)
  then '+' else '')
   "/>
   
</xsl:function>


<xsl:function name="functx:siblings-same-name" as="element()*" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="element" as="element()?"/> 
 
  <xsl:sequence select=" 
   $element/../*[node-name(.) = node-name($element)]
   except $element
 "/>
   
</xsl:function>


<xsl:function name="functx:siblings" as="node()*" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="node" as="node()?"/> 
 
  <xsl:sequence select=" 
   $node/../node() except $node
 "/>
   
</xsl:function>


<xsl:function name="functx:sort-as-numeric" as="item()*" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="seq" as="item()*"/> 
 
   <xsl:for-each select="$seq">
     <xsl:sort select="number(.)"/>
     <xsl:copy-of select="."/>
   </xsl:for-each>
 
</xsl:function>


<xsl:function name="functx:sort-case-insensitive" as="item()*" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="seq" as="item()*"/> 
 
   <xsl:for-each select="$seq">
     <xsl:sort select="upper-case(string(.))"/>
     <xsl:copy-of select="."/>
   </xsl:for-each>
 
</xsl:function>


<xsl:function name="functx:sort-document-order" as="node()*" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="seq" as="node()*"/> 
 
  <xsl:sequence select=" 
   $seq/.
 "/>
   
</xsl:function>


<xsl:function name="functx:sort" as="item()*" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="seq" as="item()*"/> 
 
   <xsl:for-each select="$seq">
     <xsl:sort select="."/>
     <xsl:copy-of select="."/>
   </xsl:for-each>
 
</xsl:function>


<xsl:function name="functx:substring-after-if-contains" as="xs:string?" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="arg" as="xs:string?"/> 
  <xsl:param name="delim" as="xs:string"/> 
 
  <xsl:sequence select=" 
   if (contains($arg,$delim))
   then substring-after($arg,$delim)
   else $arg
 "/>
   
</xsl:function>


<xsl:function name="functx:substring-after-last-match" as="xs:string" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="arg" as="xs:string?"/> 
  <xsl:param name="regex" as="xs:string"/> 
 
  <xsl:sequence select=" 
   replace($arg,concat('^.*',$regex),'')
 "/>
   
</xsl:function>


<xsl:function name="functx:substring-after-last" as="xs:string" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="arg" as="xs:string?"/> 
  <xsl:param name="delim" as="xs:string"/> 
 
  <xsl:sequence select=" 
   replace ($arg,concat('^.*',functx:escape-for-regex($delim)),'')
 "/>
   
</xsl:function>


<xsl:function name="functx:substring-after-match" as="xs:string?" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="arg" as="xs:string?"/> 
  <xsl:param name="regex" as="xs:string"/> 
 
  <xsl:sequence select=" 
   replace($arg,concat('^.*?',$regex),'')
 "/>
   
</xsl:function>


<xsl:function name="functx:substring-before-if-contains" as="xs:string?" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="arg" as="xs:string?"/> 
  <xsl:param name="delim" as="xs:string"/> 
 
  <xsl:sequence select=" 
   if (contains($arg,$delim))
   then substring-before($arg,$delim)
   else $arg
 "/>
   
</xsl:function>


<xsl:function name="functx:substring-before-last-match" as="xs:string?" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="arg" as="xs:string?"/> 
  <xsl:param name="regex" as="xs:string"/> 
 
  <xsl:sequence select=" 
   replace($arg,concat('^(.*)',$regex,'.*'),'$1')
 "/>
   
</xsl:function>


<xsl:function name="functx:substring-before-last" as="xs:string" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="arg" as="xs:string?"/> 
  <xsl:param name="delim" as="xs:string"/> 
 
  <xsl:sequence select=" 
   if (matches($arg, functx:escape-for-regex($delim)))
   then replace($arg,
            concat('^(.*)', functx:escape-for-regex($delim),'.*'),
            '$1')
   else ''
 "/>
   
</xsl:function>


<xsl:function name="functx:substring-before-match" as="xs:string" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="arg" as="xs:string?"/> 
  <xsl:param name="regex" as="xs:string"/> 
 
  <xsl:sequence select=" 
   tokenize($arg,$regex)[1]
 "/>
   
</xsl:function>


<xsl:function name="functx:time" as="xs:time" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="hour" as="xs:anyAtomicType"/> 
  <xsl:param name="minute" as="xs:anyAtomicType"/> 
  <xsl:param name="second" as="xs:anyAtomicType"/> 
 
  <xsl:sequence select=" 
   xs:time(
     concat(
       functx:pad-integer-to-length(xs:integer($hour),2),':',
       functx:pad-integer-to-length(xs:integer($minute),2),':',
       functx:pad-integer-to-length(xs:integer($second),2)))
 "/>
   
</xsl:function>


<xsl:function name="functx:timezone-from-duration" as="xs:string" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="duration" as="xs:dayTimeDuration"/> 
 
  <xsl:sequence select=" 
   if (string($duration) = ('PT0S','-PT0S'))
   then 'Z'
   else if (matches(string($duration),'-PT[1-9]H'))
   then replace(string($duration),'PT([1-9])H','0$1:00')
   else if (matches(string($duration),'PT[1-9]H'))
   then replace(string($duration),'PT([1-9])H','+0$1:00')
   else if (matches(string($duration),'-PT1[0-4]H'))
   then replace(string($duration),'PT(1[0-4])H','$1:00')
   else if (matches(string($duration),'PT1[0-4]H'))
   then replace(string($duration),'PT(1[0-4])H','+$1:00')
   else error(xs:QName('functx:Invalid_Duration_Value'))
 "/>
   
</xsl:function>


<xsl:function name="functx:total-days-from-duration" as="xs:decimal?" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="duration" as="xs:dayTimeDuration?"/> 
 
  <xsl:sequence select=" 
   $duration div xs:dayTimeDuration('P1D')
 "/>
   
</xsl:function>


<xsl:function name="functx:total-hours-from-duration" as="xs:decimal?" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="duration" as="xs:dayTimeDuration?"/> 
 
  <xsl:sequence select=" 
   $duration div xs:dayTimeDuration('PT1H')
 "/>
   
</xsl:function>


<xsl:function name="functx:total-minutes-from-duration" as="xs:decimal?" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="duration" as="xs:dayTimeDuration?"/> 
 
  <xsl:sequence select=" 
   $duration div xs:dayTimeDuration('PT1M')
 "/>
   
</xsl:function>


<xsl:function name="functx:total-months-from-duration" as="xs:decimal?" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="duration" as="xs:yearMonthDuration?"/> 
 
  <xsl:sequence select=" 
   $duration div xs:yearMonthDuration('P1M')
 "/>
   
</xsl:function>


<xsl:function name="functx:total-seconds-from-duration" as="xs:decimal?" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="duration" as="xs:dayTimeDuration?"/> 
 
  <xsl:sequence select=" 
   $duration div xs:dayTimeDuration('PT1S')
 "/>
   
</xsl:function>


<xsl:function name="functx:total-years-from-duration" as="xs:decimal?" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="duration" as="xs:yearMonthDuration?"/> 
 
  <xsl:sequence select=" 
   $duration div xs:yearMonthDuration('P1Y')
 "/>
   
</xsl:function>


<xsl:function name="functx:trim" as="xs:string" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="arg" as="xs:string?"/> 
 
  <xsl:sequence select=" 
   replace(replace($arg,'\s+$',''),'^\s+','')
 "/>
   
</xsl:function>


<xsl:function name="functx:update-attributes" as="element()?" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="elements" as="element()*"/> 
  <xsl:param name="attrNames" as="xs:QName*"/> 
  <xsl:param name="attrValues" as="xs:anyAtomicType*"/> 
 
  <xsl:for-each select="$elements">
    <xsl:variable name="element" select="."/>
    <xsl:copy>
      <xsl:for-each select="$attrNames">
        <xsl:variable name="seq" select="position()"/>
        <xsl:if test="$element/@*[node-name(.) = current()]">
          <xsl:attribute name="{.}"
                         namespace="{namespace-uri-from-QName(.)}"
                         select="$attrValues[$seq]"/>
        </xsl:if>
      </xsl:for-each>
      <xsl:copy-of select="@*[not(node-name(.) = $attrNames)]|node()"/>
    </xsl:copy>
  </xsl:for-each>
 
</xsl:function>


<xsl:function name="functx:value-except" as="xs:anyAtomicType*" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="arg1" as="xs:anyAtomicType*"/> 
  <xsl:param name="arg2" as="xs:anyAtomicType*"/> 
 
  <xsl:sequence select=" 
  distinct-values($arg1[not(.=$arg2)])
 "/>
   
</xsl:function>


<xsl:function name="functx:value-intersect" as="xs:anyAtomicType*" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="arg1" as="xs:anyAtomicType*"/> 
  <xsl:param name="arg2" as="xs:anyAtomicType*"/> 
 
  <xsl:sequence select=" 
  distinct-values($arg1[.=$arg2])
 "/>
   
</xsl:function>


<xsl:function name="functx:value-union" as="xs:anyAtomicType*" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="arg1" as="xs:anyAtomicType*"/> 
  <xsl:param name="arg2" as="xs:anyAtomicType*"/> 
 
  <xsl:sequence select=" 
  distinct-values(($arg1, $arg2))
 "/>
   
</xsl:function>


<xsl:function name="functx:word-count" as="xs:integer" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="arg" as="xs:string?"/> 
 
  <xsl:sequence select=" 
   count(tokenize($arg, '\W+')[. != ''])
 "/>
   
</xsl:function>


<xsl:function name="functx:words-to-camel-case" as="xs:string" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="arg" as="xs:string?"/> 
 
  <xsl:sequence select=" 
     string-join((tokenize($arg,'\s+')[1],
       for $word in tokenize($arg,'\s+')[position() > 1]
       return functx:capitalize-first($word))
      ,'')
 "/>
   
</xsl:function>


<xsl:function name="functx:wrap-values-in-elements" as="element()*" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="values" as="xs:anyAtomicType*"/> 
  <xsl:param name="elementName" as="xs:QName"/> 
 
   <xsl:for-each select="$values">
     <xsl:element name="{$elementName}"
                  namespace="{namespace-uri-from-QName($elementName)}">
       <xsl:sequence select="."/>
     </xsl:element>
   </xsl:for-each>
 
</xsl:function>


<xsl:function name="functx:yearMonthDuration" as="xs:yearMonthDuration" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="years" as="xs:decimal?"/> 
  <xsl:param name="months" as="xs:integer?"/> 
 
  <xsl:sequence select=" 
    (xs:yearMonthDuration('P1M') * functx:if-empty($months,0)) +
    (xs:yearMonthDuration('P1Y') * functx:if-empty($years,0))
 "/>
   
</xsl:function>


</xsl:stylesheet>
