   M S B A M L   `   `   `  ����@  <Laba4, Version=1.0.0.0, Culture=neutral, PublicKeyToken=nullclr-namespace:Laba4Laba4  5          Laba4.UserControl1   5      W SPresentationCore, Version=6.0.2.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=6.0.2.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35e aSystem.Windows.Controls.Ribbon, Version=6.0.2.0, Culture=neutral, PublicKeyToken=b77a5c561934e089R NWindowsBase, Version=6.0.2.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35F 9http://schemas.microsoft.com/winfx/2006/xaml/presentation     5      R NSystem.Xaml, Version=6.0.2.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5      Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5      @d2http://schemas.microsoft.com/expression/blend/2008     5      %localclr-namespace:Laba4     5        � 	Resources  5
         ButtonStyle �� 
TargetType �� Property �� Value  ForegroundColor  BackgroundColor  FadeInOutAnimation �� TargetProperty W� From	 W� To g� Duration��%�  &	        &	 N    �� 5   
   " ��6$   .�5      ��  � ��$ 30��6'   �� 5       � ��$	 200��6&   �� 5       � ��# �  6+   �� 5       � ��# �  6+   �� 5       � ��$
 Bold"�6+   �� 5       � ��$ Center=�64   �� 5       � ��$ 	0,10,0,10q�6'   �� 5       � ��$ 16(�6)   5      �� 5   
   .��5      W� $ Opacity�6    06B    16K   $ 0:0:1D�6R   5      5       � Triggers 5      :� 5   
   	 :� RoutedEvent$	 FrameworkElement.Loaded��6   .[�5      �� #��[ 6   5      .��5#      � 
 � RowDefinitions
 5$   
   �� 5%      $
��Auto �6   �� 5&      $
��Auto �6   �� 5'      $
��Auto �6   �� 5(      $
��Auto �6   �� 5)      $
��Auto �6    � ColumnDefinitions 5+   
   �� 5,      $��* �6   �� 5-      $
��Auto �6   .+�50   
   ��   String54#���  6   $��5q�66   $��0��6A   �� 51   
   $��Center=�6    �� Orientation$ 
Horizontal=�60   $��0��6I   $��1��6V   .+�52      �� ��6   ��  �� ElementName$ NameTextBox�� �� Path$ Text.Length��� 53      $��/��6   �� 54      $��30��6   55      �� 56   
   -   5         ��Name$ NameTextBox��56   A   $��30��6   $��2��6    �� 	MaxLength$ 30��62   $��1��6V   �� 58   
     String53#���  6   $��2��66   $��5q�6C   �� 59   
   $��Center=�6   $ 
Horizontal=�60   $��2��6I   $��1��6V   .+�5:      �� ��6   �� $ CommentTextBox��$ Text.Length��� 5;      $��/��6   �� 5<      $	��300��6   5=      �� 5?   
   -   5        $ CommentTextBox��5?   B   $��60��6   $��2��6   $	 300��62   $��3��6Z    �� TextWrapping$
 Wrap=�6g   �� 5A   
   -   5          String52#���  5A      $��4��66   #��[  6\   5B      5D      