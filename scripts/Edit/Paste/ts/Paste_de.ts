<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="de_DE">
<context>
    <name>Paste</name>
    <message>
        <location filename="../Paste.js" line="+75"/>
        <source>Position</source>
        <translation>Position</translation>
    </message>
    <message>
        <location filename="../PasteInit.js" line="+2"/>
        <source>&amp;Paste</source>
        <translation>Ein&amp;fügen</translation>
    </message>
    <message>
        <location filename="../Paste.ui" line="+17"/>
        <source>Rotation:</source>
        <translation>Rotation:</translation>
    </message>
    <message>
        <source>150</source>
        <translation type="obsolete">150</translation>
    </message>
    <message>
        <source>300</source>
        <translation type="obsolete">300</translation>
    </message>
    <message>
        <location line="+110"/>
        <source>Scale:</source>
        <translation>Skalierung:</translation>
    </message>
    <message>
        <source>3</source>
        <translation type="obsolete">3</translation>
    </message>
    <message>
        <source>4</source>
        <translation type="obsolete">4</translation>
    </message>
    <message>
        <source>5</source>
        <translation type="obsolete">5</translation>
    </message>
    <message>
        <location line="+123"/>
        <source>To current layer</source>
        <translation>Auf aktuellen Layer</translation>
    </message>
    <message>
        <source>&lt;html&gt; &lt;head&gt; &lt;title&gt;QCad User Reference Manual - Basic Editing Commands&lt;/title&gt; &lt;/head&gt; &lt;body&gt; &lt;br&gt;&lt;/br&gt; &lt;h1&gt;10. Basic Editing Commands&lt;/h1&gt; &lt;p&gt;This chapter lists the basic edit commands of QCad. These commands are not CAD specific and often also available in other applications. For CAD specific editing commands, please refer to chapter &amp;quot;Modification&amp;quot;.&lt;/p&gt; &lt;a name=&apos;1&apos;&gt;&lt;/a&gt; &lt;h2&gt; &lt;a name=&apos;5&apos;&gt;10.5. Paste&lt;/a&gt; &lt;/h2&gt; &lt;a name=&apos;paste&apos; id=&apos;paste&apos;&gt;&lt;/a&gt; &lt;a name=&apos;edit - paste&apos; id=&apos;edit - paste&apos;&gt;&lt;/a&gt; &lt;p&gt; &lt;strong&gt;Toolbar:&lt;/strong&gt; &lt;/p&gt; &lt;p&gt; &lt;img src=&apos;img/toolbar_edit_paste.png&apos;&gt;&lt;/img&gt; &lt;/p&gt; &lt;p&gt; &lt;strong&gt;Menu:&lt;/strong&gt; &lt;/p&gt; &lt;pre&gt; Edit - Paste &lt;/pre&gt; &lt;p&gt; &lt;strong&gt;Hotkey:&lt;/strong&gt; &lt;/p&gt; &lt;pre&gt; Ctrl-V &lt;/pre&gt; &lt;p&gt; &lt;strong&gt;Command:&lt;/strong&gt; &lt;/p&gt; &lt;pre&gt; paste, ps &lt;/pre&gt; &lt;p&gt; &lt;strong&gt;Description:&lt;/strong&gt; &lt;/p&gt; &lt;p&gt; The paste command inserts the entities previously copied to the clipboard. Paste is especially useful to transfer entities from one drawing to another.&lt;br&gt;&lt;/br&gt; All layers needed by the clipboard contents are pasted into the layerlist. Existing layers with the same name don&apos;t get overwritten. Sometimes this might lead to unexpected results. If an entity gets its attributes from the layer, it might be red in the original drawing and appear green in the drawing where you paste it. That is the case if a layer exists in both drawings with different attributes.&lt;br&gt;&lt;/br&gt; Inserts (references to blocks) that are on the clipboard will be pasted together with the blocks they refer to. Blocks in the current drawing don&apos;t get overwritten. This might lead to totally unexpected results in some cases. Make sure that different blocks never have the same name in drawings for which you use the copy / paste tools.&lt;/p&gt; &lt;p&gt; &lt;strong&gt;Procedure:&lt;/strong&gt; &lt;/p&gt; &lt;ol&gt; &lt;li&gt;Activate the paste function.&lt;/li&gt; &lt;li&gt;Set the target point of for the pasted entities with the mouse or enter a coordinate in the command line. The target point corresponds to the reference point that was chosen when copying or cutting the entities.&lt;/li&gt; &lt;/ol&gt; &lt;br&gt;&lt;/br&gt; &lt;/body&gt;  &lt;/html&gt;</source>
        <translation type="obsolete">&lt;html&gt; &lt;head&gt; &lt;title&gt;QCad Benutzerhandbuch - Basic Editing Commands&lt;/title&gt; &lt;/head&gt; &lt;body&gt; &lt;br&gt;&lt;/br&gt; &lt;h1&gt;10. Grundlegende Bearbeitungsbefehle&lt;/h1&gt; &lt;p&gt;This chapter lists the basic edit commands of QCad. These commands are not CAD specific and often also available in other applications. For CAD specific editing commands, please refer to chapter &amp;quot;Modification&amp;quot;.&lt;/p&gt; &lt;a name=&apos;1&apos;&gt;&lt;/a&gt; &lt;h2&gt; &lt;a name=&apos;5&apos;&gt;10.5. Paste&lt;/a&gt; &lt;/h2&gt; &lt;a name=&apos;paste&apos; id=&apos;paste&apos;&gt;&lt;/a&gt; &lt;a name=&apos;edit - paste&apos; id=&apos;edit - paste&apos;&gt;&lt;/a&gt; &lt;p&gt; &lt;strong&gt;Toolbar:&lt;/strong&gt; &lt;/p&gt; &lt;p&gt; &lt;img src=&apos;img/toolbar_edit_paste.png&apos;&gt;&lt;/img&gt; &lt;/p&gt; &lt;p&gt; &lt;strong&gt;Menu:&lt;/strong&gt; &lt;/p&gt; &lt;pre&gt; Edit - Paste &lt;/pre&gt; &lt;p&gt; &lt;strong&gt;Hotkey:&lt;/strong&gt; &lt;/p&gt; &lt;pre&gt; Ctrl-V &lt;/pre&gt; &lt;p&gt; &lt;strong&gt;Command:&lt;/strong&gt; &lt;/p&gt; &lt;pre&gt; paste, ps &lt;/pre&gt; &lt;p&gt; &lt;strong&gt;Description:&lt;/strong&gt; &lt;/p&gt; &lt;p&gt; The paste command inserts the entities previously copied to the clipboard. Paste is especially useful to transfer entities from one drawing to another.&lt;br&gt;&lt;/br&gt; All layers needed by the clipboard contents are pasted into the layerlist. Existing layers with the same name don&apos;t get overwritten. Sometimes this might lead to unexpected results. If an entity gets its attributes from the layer, it might be red in the original drawing and appear green in the drawing where you paste it. That is the case if a layer exists in both drawings with different attributes.&lt;br&gt;&lt;/br&gt; Inserts (references to blocks) that are on the clipboard will be pasted together with the blocks they refer to. Blocks in the current drawing don&apos;t get overwritten. This might lead to totally unexpected results in some cases. Make sure that different blocks never have the same name in drawings for which you use the copy / paste tools.&lt;/p&gt; &lt;p&gt; &lt;strong&gt;Procedure:&lt;/strong&gt; &lt;/p&gt; &lt;ol&gt; &lt;li&gt;Activate the paste function.&lt;/li&gt; &lt;li&gt;Set the target point of for the pasted entities with the mouse or enter a coordinate in the command line. The target point corresponds to the reference point that was chosen when copying or cutting the entities.&lt;/li&gt; &lt;/ol&gt; &lt;br&gt;&lt;/br&gt; &lt;/body&gt;  &lt;/html&gt;</translation>
    </message>
    <message>
        <source>&lt;html&gt; &lt;head&gt; &lt;title&gt;QCad User Reference Manual - Basic Editing Commands&lt;/title&gt; &lt;/head&gt; &lt;body&gt; &lt;br&gt;&lt;/br&gt; &lt;h1&gt;10. Basic Editing Commands&lt;/h1&gt; &lt;p&gt;This chapter lists the basic edit commands of QCad. These commands are not CAD specific and often also available in other applications. For CAD specific editing commands, please refer to chapter &amp;quot;Modification&amp;quot;.&lt;/p&gt; &lt;a name=&apos;1&apos;&gt;link&lt;/a&gt; &lt;h2&gt; &lt;a name=&apos;5&apos;&gt;10.5. Paste&lt;/a&gt; &lt;/h2&gt; &lt;a name=&apos;paste&apos; id=&apos;paste&apos;&gt;&lt;/a&gt; &lt;a name=&apos;edit - paste&apos; id=&apos;edit - paste&apos;&gt;&lt;/a&gt; &lt;p&gt; &lt;strong&gt;Toolbar:&lt;/strong&gt; &lt;/p&gt; &lt;p&gt; &lt;img src=&apos;img/toolbar_edit_paste.png&apos;&gt;&lt;/img&gt; &lt;/p&gt; &lt;p&gt; &lt;strong&gt;Menu:&lt;/strong&gt; &lt;/p&gt; &lt;pre&gt; Edit - Paste &lt;/pre&gt; &lt;p&gt; &lt;strong&gt;Hotkey:&lt;/strong&gt; &lt;/p&gt; &lt;pre&gt; Ctrl-V &lt;/pre&gt; &lt;p&gt; &lt;strong&gt;Command:&lt;/strong&gt; &lt;/p&gt; &lt;pre&gt; paste, ps &lt;/pre&gt; &lt;p&gt; &lt;strong&gt;Description:&lt;/strong&gt; &lt;/p&gt; &lt;p&gt; The paste command inserts the entities previously copied to the clipboard. Paste is especially useful to transfer entities from one drawing to another.&lt;br&gt;&lt;/br&gt; All layers needed by the clipboard contents are pasted into the layerlist. Existing layers with the same name don&apos;t get overwritten. Sometimes this might lead to unexpected results. If an entity gets its attributes from the layer, it might be red in the original drawing and appear green in the drawing where you paste it. That is the case if a layer exists in both drawings with different attributes.&lt;br&gt;&lt;/br&gt; Inserts (references to blocks) that are on the clipboard will be pasted together with the blocks they refer to. Blocks in the current drawing don&apos;t get overwritten. This might lead to totally unexpected results in some cases. Make sure that different blocks never have the same name in drawings for which you use the copy / paste tools.&lt;/p&gt; &lt;p&gt; &lt;strong&gt;Procedure:&lt;/strong&gt; &lt;/p&gt; &lt;ol&gt; &lt;li&gt;Activate the paste function.&lt;/li&gt; &lt;li&gt;Set the target point of for the pasted entities with the mouse or enter a coordinate in the command line. The target point corresponds to the reference point that was chosen when copying or cutting the entities.&lt;/li&gt; &lt;/ol&gt; &lt;br&gt;&lt;/br&gt; &lt;/body&gt;  &lt;/html&gt;</source>
        <translation type="obsolete">&lt;html&gt; &lt;head&gt; &lt;title&gt;QCad User Reference Manual - Basic Editing Commands&lt;/title&gt; &lt;/head&gt; &lt;body&gt; &lt;br&gt;&lt;/br&gt; &lt;h1&gt;10. Grundlegende Bearbeitungsbefehle&lt;/h1&gt; &lt;p&gt;This chapter lists the basic edit commands of QCad. These commands are not CAD specific and often also available in other applications. For CAD specific editing commands, please refer to chapter &amp;quot;Modification&amp;quot;.&lt;/p&gt; &lt;a name=&apos;1&apos;&gt;link&lt;/a&gt; &lt;h2&gt; &lt;a name=&apos;5&apos;&gt;10.5. Paste&lt;/a&gt; &lt;/h2&gt; &lt;a name=&apos;paste&apos; id=&apos;paste&apos;&gt;&lt;/a&gt; &lt;a name=&apos;edit - paste&apos; id=&apos;edit - paste&apos;&gt;&lt;/a&gt; &lt;p&gt; &lt;strong&gt;Toolbar:&lt;/strong&gt; &lt;/p&gt; &lt;p&gt; &lt;img src=&apos;img/toolbar_edit_paste.png&apos;&gt;&lt;/img&gt; &lt;/p&gt; &lt;p&gt; &lt;strong&gt;Menu:&lt;/strong&gt; &lt;/p&gt; &lt;pre&gt; Edit - Paste &lt;/pre&gt; &lt;p&gt; &lt;strong&gt;Hotkey:&lt;/strong&gt; &lt;/p&gt; &lt;pre&gt; Ctrl-V &lt;/pre&gt; &lt;p&gt; &lt;strong&gt;Command:&lt;/strong&gt; &lt;/p&gt; &lt;pre&gt; paste, ps &lt;/pre&gt; &lt;p&gt; &lt;strong&gt;Description:&lt;/strong&gt; &lt;/p&gt; &lt;p&gt; The paste command inserts the entities previously copied to the clipboard. Paste is especially useful to transfer entities from one drawing to another.&lt;br&gt;&lt;/br&gt; All layers needed by the clipboard contents are pasted into the layerlist. Existing layers with the same name don&apos;t get overwritten. Sometimes this might lead to unexpected results. If an entity gets its attributes from the layer, it might be red in the original drawing and appear green in the drawing where you paste it. That is the case if a layer exists in both drawings with different attributes.&lt;br&gt;&lt;/br&gt; Inserts (references to blocks) that are on the clipboard will be pasted together with the blocks they refer to. Blocks in the current drawing don&apos;t get overwritten. This might lead to totally unexpected results in some cases. Make sure that different blocks never have the same name in drawings for which you use the copy / paste tools.&lt;/p&gt; &lt;p&gt; &lt;strong&gt;Procedure:&lt;/strong&gt; &lt;/p&gt; &lt;ol&gt; &lt;li&gt;Activate the paste function.&lt;/li&gt; &lt;li&gt;Set the target point of for the pasted entities with the mouse or enter a coordinate in the command line. The target point corresponds to the reference point that was chosen when copying or cutting the entities.&lt;/li&gt; &lt;/ol&gt; &lt;br&gt;&lt;/br&gt; &lt;/body&gt;  &lt;/html&gt;</translation>
    </message>
    <message>
        <location line="-220"/>
        <source>Rotate pasted entities&lt;br&gt;by this angle</source>
        <translation>Eingefügte Elemente um&lt;br&gt;diesen Winkel rotieren</translation>
    </message>
    <message>
        <source>30</source>
        <translation type="obsolete">30</translation>
    </message>
    <message>
        <source>45</source>
        <translation type="obsolete">45</translation>
    </message>
    <message>
        <source>60</source>
        <translation type="obsolete">60</translation>
    </message>
    <message>
        <source>120</source>
        <translation type="obsolete">120</translation>
    </message>
    <message>
        <source>135</source>
        <translation type="obsolete">135</translation>
    </message>
    <message>
        <source>210</source>
        <translation type="obsolete">210</translation>
    </message>
    <message>
        <source>225</source>
        <translation type="obsolete">225</translation>
    </message>
    <message>
        <source>240</source>
        <translation type="obsolete">240</translation>
    </message>
    <message>
        <source>315</source>
        <translation type="obsolete">315</translation>
    </message>
    <message>
        <source>330</source>
        <translation type="obsolete">330</translation>
    </message>
    <message>
        <location line="+110"/>
        <source>Scale pasted entities&lt;br&gt;by this factor</source>
        <translation>Eingefügte Elemente um&lt;br&gt;diesen Faktor skalieren</translation>
    </message>
    <message>
        <source>1/3</source>
        <translation type="obsolete">1/3</translation>
    </message>
    <message>
        <source>1/4</source>
        <translation type="obsolete">1/4</translation>
    </message>
    <message>
        <source>1/5</source>
        <translation type="obsolete">1/5</translation>
    </message>
    <message>
        <location line="+72"/>
        <source>Flip pasted entities&lt;br&gt;horizontally</source>
        <translation>Eingefügte Elemente&lt;br&gt;horizontal spiegeln</translation>
    </message>
    <message>
        <location line="+14"/>
        <source>Flip pasted entities&lt;br&gt;vertically</source>
        <translation>Eingefügte Elemente&lt;br&gt;vertikal spiegeln</translation>
    </message>
    <message>
        <location line="+21"/>
        <source>Paste all entities&lt;br&gt;to current layer&lt;br&gt;instead of original layer</source>
        <translation>Alle Elemente auf&lt;br&gt;aktuellen Layer einfügen&lt;br&gt;statt auf originalen Layer</translation>
    </message>
    <message>
        <location line="+10"/>
        <source>Overwrite existing layers&lt;br&gt;in drawing with&lt;br&gt;layers from clipboard</source>
        <translation>Existierende Layer der&lt;br&gt;Zeichnung mit Layern aus&lt;br&gt;der Zwischenablage überschreiben</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>Overwrite layers</source>
        <translation>Layer überschreiben</translation>
    </message>
    <message>
        <location line="+7"/>
        <source>Overwrite existing blocks&lt;br&gt;in drawing with&lt;br&gt;blocks from clipboard</source>
        <translation>Existierende Blöcke der&lt;br&gt;Zeichnung mit Blöcken aus&lt;br&gt;der Zwischenablage überschreiben</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>Overwrite blocks</source>
        <translation>Blöcke überschreiben</translation>
    </message>
</context>
</TS>
